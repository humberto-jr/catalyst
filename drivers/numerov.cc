#include "modules/essentials.h"
#include "modules/numerov.h"
#include "modules/libmpi.h"
#include "modules/input.h"
#include "modules/timer.h"
#include "modules/math.h"
#include "modules/file.h"

// Internals
#include "filename.h"
#include "key.h"

constexpr u8 FORMAT_VERSION = 2;

struct job {
	mut<u32> index;
	mat<f64> ratio;
	mut<f64> tot_energy;

	inline job(usize channel_count): index(0), ratio(channel_count, channel_count), tot_energy(0.0)
	{
	}

	void operator=(job &&other)
	{
		this->index = other.index;
		this->ratio.swap(other.ratio);
		this->tot_energy = other.tot_energy;
	}
};

int main(int argc, char *argv[])
{
	mpi::frontend mpi(&argc, &argv);

	//
	// Coupling potential:
	//

	string potname = mpi.input_keyword(key::coupling_input_filename, filename::coupling_matrix);

	numerov::potential coupling = numerov::open(potname);

	u32 R_count = as_u32((coupling.R_max - coupling.R_min)/coupling.R_step);

	usize channel_count = coupling[0].rows();

	//
	// Collision energy grid:
	//

	u32 E_count = mpi.input_keyword(key::coll_grid_size, 1u, u32_max, 1u);

	f64 E_min = mpi.input_keyword(key::E_min, 0.0, f64_max, 0.0);

	f64 E_max = mpi.input_keyword(key::E_max, E_min, f64_max, E_min);

	f64 E_step = (E_max - E_min)/as_f64(E_count);

	mpi.set_tasks(E_count);

	u32 chunk_count = (mpi.extra_task().has_value()? mpi.task_count() + 1 : mpi.task_count());

	//
	// Setup of the propagation matrices:
	//

	mut<usize> memory_used = 0;

	vec<job> task(chunk_count);

	for (mut<u32> n = 0; n < chunk_count; ++n) {
		task[n] = job(channel_count);
		memory_used += task[n].ratio.size();
	}

	mat<f64> old_ratio(channel_count, channel_count);
	mat<f64> workspace(channel_count, channel_count);

	// NOTE: This amounts to three extra matrices: The old_ratio, the workspace,
	// and the potential matrix. Some processes may have an extra step (matrix),
	// which is taken into account here. Therefore, the reported memory usage
	// may slightly overestimate that of some processes.
	memory_used += 3*old_ratio.size();

	//
	// Numerov solutions: Only the master process will open the output file later.
	//

	string bufname = mpi.input_keyword(key::numerov_output_filename, filename::ratio_matrix);

	//
	// Summary:
	//

	if (mpi.rank() == mpi::MASTER_PROCESS_RANK) {
		print::timestamp();
		print::line("# MPI procs.: ", mpi.world_size());
		print::line("# Grid size: ", R_count);
		print::line("# Coupled channels: ", channel_count);
		print::line("# Coupling potential: ", coupling.filename());
		print::line("# Numerov solutions: ", bufname.as_cstr());
		print::line("# Approx. memory usage: ", as_f32(memory_used/1000000u), " MB/process");
		print::line("# Reduced mass: ", coupling.mass, " a.u.");
		print::line("#");
		print::line("#  Grid   Proc.      I/O time (s)       prop. time (s)     total (s)");
		print::line("# ---------------------------------------------------------------------");
	}

	//
	// Propagation:
	//

	for (mut<u32> n = 0; n < R_count; ++n) {
		timer<2> clock;

		clock.start();
		const mat<f64>& pot_energy = coupling[n];
		clock.stop();

		// NOTE: The m-th energy index used below is relative to each process,
		// thus the task vector is indexed using the count variable.
		mut<usize> count = 0;

		clock.start();

		for (mut<u32> m = mpi.first_local_task(); m <= mpi.last_local_task(); ++m) {
			extra_step:

			if (n == 0) {
				task[count].index = m;
				task[count].tot_energy = E_min + as_f64(m)*E_step;
			}

			task[count].ratio.swap(old_ratio);

			numerov::renormalized(coupling.mass,
			                      coupling.R_step,
			                      task[count].tot_energy, pot_energy,
			                      workspace, old_ratio, task[count].ratio);
			++count;

			if (m == mpi.last_local_task()) {
				auto index = mpi.extra_task();

				if (index.has_value()) {
					m = index.value();
					goto extra_step;
				}
			}
		}

		clock.stop();

		print::line<7>(n, mpi.rank(), ' ', as_f32(clock[0]), ' ', as_f32(clock[1]), ' ', as_f32(clock[0] + clock[1]));
	}

	//
	// Sorting: If MPI is used, the master process will now receive all Numerov
	// ratio matrices ordered by ranks (energy) and write them on the output.
	//

	if (mpi.rank() == mpi::MASTER_PROCESS_RANK) {
		file::output solution(bufname);

		solution.write(numerov::MAGIC_NUMBER);
		solution.write(FORMAT_VERSION);
		solution.write(coupling.R_max);
		solution.write(coupling.R_step);
		solution.write(coupling.mass);
		solution.write(channel_count);
		solution.write(E_min);
		solution.write(E_max);
		solution.write(E_step);

		for (mut<u32> n = 0; n < chunk_count; ++n) {
			solution.write(task[n].index);
			solution.write(task[n].tot_energy);
			solution.write(task[n].ratio);
		}

		for (mut<u32> rank = 1; rank < mpi.world_size(); ++rank) {
			mut<u32> next_chunk = 0;
			mpi.receive(rank, next_chunk);

			assert(chunk_count >= next_chunk);

			for (mut<u32> n = 0; n < next_chunk; ++n) {
				mpi.receive(rank, task[n].index);
				mpi.receive(rank, task[n].tot_energy);
				mpi.receive(rank, task[n].ratio);

				if (task[n].index > mpi.last_local_task()) {
					solution.write(task[n].index);
					solution.write(task[n].tot_energy);
					solution.write(task[n].ratio);
				}
			}
		}
	} else {
		mpi.send(mpi::MASTER_PROCESS_RANK, chunk_count);

		for (mut<u32> n = 0; n < chunk_count; ++n) {
			mpi.send(mpi::MASTER_PROCESS_RANK, task[n].index);
			mpi.send(mpi::MASTER_PROCESS_RANK, task[n].tot_energy);
			mpi.send(mpi::MASTER_PROCESS_RANK, task[n].ratio);
		}
	}

	return EXIT_SUCCESS;
}
