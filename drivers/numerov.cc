#include "modules/essentials.h"
#include "modules/numerov.h"
#include "modules/timer.h"
#include "modules/libtoml.h"

constexpr u8 FORMAT_VERSION = 2;

struct Job {
	mut<usize> index;
	mut<f64> energy;
	Mat<f64> ratio;
};

int main(int argc, char *argv[])
{
	mpi::Frontend mpi(&argc, &argv);

	if (mpi.rank() == mpi::MASTER_PROCESS_RANK) {
		print::line("# ", argv[0]);
		print::timestamp();
		print::line();
	}

	toml::Cin toml;

	//
	// Coupling potential:
	//

	c_str potname = toml.string("coupling_matrix", "filename", "atom+diatom_coupling_matrix.bin", &mpi);

	numerov::Potential coupling(potname);

	f64 mass = coupling.reduced_mass();

	usize channel_count = coupling.channel_count();

	Range<f64> R_list = coupling.grid_range();

	//
	// Collision energy: Chunks of energy values will be handled by each
	// MPI process, with every energy referred to as a task. Each process
	// will accommodate one extra task for the remainder when the total
	// of energies does not divide evenly among processes.
	//

	Range<f64> energy_list = toml.range("numerov", 0.0, 0.0, 0.0, &mpi);

	if (energy_list.as_range_inclusive().count() == 0) {
		 print::error(WHERE, "Expecting the range of collision energies at numerov.min, numerov.max, and numerov.step");
	}

	mpi.set_tasks(energy_list.count());

	usize chunk_size = mpi.task_count() + 1;

	//
	// Summary:
	//

	if (mpi.rank() == mpi::MASTER_PROCESS_RANK) {
		print::line();
		print::line("# Grid size: ", R_list.count());
		print::line("# Channel count: ", channel_count);
		print::line("# Reduced mass: ", mass, " a.u.");
		print::line("#");
		print::line("# MPI proc.                  R (a.u.)                  I/O time (s)                prop. time (s)                total time (s)");
		print::line("# --------------------------------------------------------------------------------------------------------------------------------");
	}

	//
	// Propagation of all collision energies for each R-value:
	//

	Vec<Job> result(chunk_size);
	Mat<f64> workspace(channel_count, channel_count);
	Mat<f64> prev_ratio(channel_count, channel_count);

	for (auto R : R_list.indexed()) {
		Timer<2> clock;

		clock.start();
		auto &potential = coupling[R.index];
		clock.stop();

		// NOTE: The n-th energy index used below (task) is relative to each
		// MPI process, thus the job list is indexed using the count variable.
		mut<usize> count = 0;

		clock.start();

		for (mut<usize> task = mpi.first_local_task(); task <= mpi.last_local_task(); ++task) {
			extra_step:

			if (R.index == 0) {
				result[count].index = task;
				result[count].energy = energy_list[task];
				result[count].ratio.resize(channel_count, channel_count);
			}

			// NOTE: When swapping the matrices, the current result ratio will
			// hold garbage data temporarily, but the Numerov routine will only
			// rewrite it with the updated ratio matrix. We take advantage of
			// this write-only feature to avoid zeroing the whole matrix every
			// step, which can become expensive.
			prev_ratio.swap(result[count].ratio);

			numerov::renormalized(mass,
			                      R_list.step,
			                      energy_list[task],
			                      potential.value, workspace, prev_ratio, result[count].ratio);
			++count;

			if (task == mpi.last_local_task()) {
				auto index = mpi.extra_task();

				if (index.has_value()) {
					task = index.value();
					goto extra_step;
				}
			}
		}

		clock.stop();

		print::line<9, '#'>(mpi.rank(), ' ', R.value, ' ', clock[0], ' ', clock[1], ' ', clock[0] + clock[1]);
	}

	//
	// Send all ratio matrices, their energy index, and energy value to the master process:
	//

	usize extra_task = chunk_size - 1;

	if (mpi.rank() == mpi::MASTER_PROCESS_RANK) {
		file::Output solution = toml.output_filename("numerov", "numerov_ratio_matrix.bin");

		solution.write(numerov::MAGIC_NUMBER);
		solution.write(FORMAT_VERSION);
		solution.write(channel_count);
		solution.write(mass);
		solution.write(R_list);
		solution.write(energy_list);

		for (mut<usize> task = 0; task < extra_task; ++task) {
			solution.write(result[task].index);
			solution.write(result[task].energy);
			solution.write(result[task].ratio);
		}

		for (mut<u32> rank = 1; rank < mpi.world_size(); ++rank) {
			for (mut<usize> task = 0; task < extra_task; ++task) {
				mpi.receive(rank, result[task].index);
				mpi.receive(rank, result[task].energy);
				mpi.receive(rank, result[task].ratio);

			 	solution.write(result[task].index);
			 	solution.write(result[task].energy);
			 	solution.write(result[task].ratio);
			}
		}

		if (result[extra_task].index > 0) {
			solution.write(result[extra_task].index);
			solution.write(result[extra_task].energy);
			solution.write(result[extra_task].ratio);
		}

		for (mut<u32> rank = 1; rank < mpi.world_size(); ++rank) {
			mpi.receive(rank, result[extra_task].index);

			if (result[extra_task].index > 0) {
				mpi.receive(rank, result[extra_task].energy);
				mpi.receive(rank, result[extra_task].ratio);

				solution.write(result[extra_task].index);
				solution.write(result[extra_task].energy);
				solution.write(result[extra_task].ratio);
			}
		}
	} else {
		for (mut<usize> task = 0; task < extra_task; ++task) {
			mpi.send(mpi::MASTER_PROCESS_RANK, result[task].index);
			mpi.send(mpi::MASTER_PROCESS_RANK, result[task].energy);
			mpi.send(mpi::MASTER_PROCESS_RANK, result[task].ratio);
		}

		// NOTE: If the extra task is unused, its index is set to zero,
		// which is invalid, and will let the master process know that
		// it is to be skipped. In these cases the ratio matrix is not
		// allocated either.
		mpi.send(mpi::MASTER_PROCESS_RANK, result[extra_task].index);

		if (result[extra_task].index > 0) {
			mpi.send(mpi::MASTER_PROCESS_RANK, result[extra_task].energy);
			mpi.send(mpi::MASTER_PROCESS_RANK, result[extra_task].ratio);
		}
	}

	return EXIT_SUCCESS;
}
