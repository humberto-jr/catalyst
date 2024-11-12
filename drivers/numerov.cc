#include "modules/essentials.h"
#include "modules/numerov.h"
#include "modules/struct.h"
#include "modules/timer.h"
#include "user.h"

constexpr u8 FORMAT_VERSION = 2;

void setup_task_list(Mat<Struct> &list, usize channel_count)
{
	for (mut<usize> task = 0; task < list.length(); ++task) {
		list[task].push_member<usize>();
		list[task].push_member<usize>();
		list[task].push_member<f64>();
		list[task].push_member<f64>();
		list[task].push_member<f64>(channel_count*channel_count);
	}
}

int main(int argc, char *argv[])
{
	mpi::Frontend mpi(&argc, &argv);

	//
	// Coupling potential:
	//

	String filename = user::coupling_input_file(&mpi);

	numerov::Potential coupling(filename.as_cstr());

	f64 mass = coupling.reduced_mass();

	usize channel_count = coupling.channel_count();

	const Range<f64> R_list = coupling.grid_range();

	//
	// Collision energy grid:
	//

	const Range<f64> energy_list = user::total_energy_grid(&mpi);

	mpi.set_tasks(energy_list.count());

	usize chunk_count = mpi.task_count() + 1;

	//
	// The Job struct: Stores both grid indices, the R value, the collision energy,
	// and the respective ratio matrix. It uses the Struct type to easily serialize
	// and deserialize all data. A matrix of size MPI processes by collision
	// energies will hold all tasks ordered in the MPI master process.
	//
	// Layout example:
	//
	// struct Job {
	//	 mut<usize> grid_index;
	//	 mut<usize> energy_index;
	//   mut<f64> R;
	//   mut<f64> total_energy;
	//	 Mat<f64> ratio;
	// };

	Mat<Struct> list(1, chunk_count);

	if ((mpi.rank() == mpi::MASTER_PROCESS_RANK) && (mpi.world_size() > 1)) {
		list.resize(mpi.world_size(), chunk_count);
	}

	setup_task_list(list, channel_count);

	//
	// Numerov solutions: Only the MPI master process will write to it.
	//

	file::Output solution = user::numerov_output_file(&mpi);

	//
	// Summary:
	//

	if (mpi.rank() == mpi::MASTER_PROCESS_RANK) {
		print::timestamp();
		print::line("# MPI procs.: ", mpi.world_size());
		print::line("# Grid size: ", R_list.count());
		print::line("# Channel count: ", channel_count);
		print::line("# Coupling input: ", coupling.filename());
		print::line("# Solution output: ", solution.filename.as_cstr());
		print::line("# Reduced mass: ", mass, " a.u.");
		print::line("#");
		print::line("# Proc.                    R (a.u.)                I/O time (s)              prop. time (s)              total time (s)");
	}

	//
	// Step 1: Propagation of all collision energies for each R-value:
	//

	Mat<f64> workspace(channel_count, channel_count);
	Mat<f64> prev_ratio(channel_count, channel_count);

	for (auto R : R_list.as_range_inclusive().indexed()) {
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
				list(0, count).dereference<usize>(0) = R.index;
				list(0, count).dereference<usize>(1) = task;
				list(0, count).dereference<f64>(2) = R.value;
				list(0, count).dereference<f64>(3) = energy_list[task];
			}

			Mat<f64> next_ratio = list(0, count).dereference_as_mat<f64>(4, channel_count, channel_count);

			prev_ratio = next_ratio;

			numerov::renormalized(mass,
			                      R_list.step,
			                      energy_list[task],
			                      potential.value, workspace, prev_ratio, next_ratio);
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

		print::line<7>(mpi.rank(), ' ', R.value, ' ', clock[0], ' ', clock[1], ' ', clock[0] + clock[1]);
	}

	//
	// Step 2: Send all Numerov ratio matrices to the MPI master process:
	//

	if (mpi.rank() == mpi::MASTER_PROCESS_RANK) {
		for (mut<u32> rank = 1; rank < mpi.world_size(); ++rank) {
			for (mut<usize> task = 0; task < chunk_count; ++task) {
				mpi.receive(rank, list(rank, task));
			}
		}
	} else {
		for (mut<usize> task = 0; task < chunk_count; ++task) {
			mpi.send(mpi::MASTER_PROCESS_RANK, list(0, task));
		}
	}

	//
	// Step 3: The MPI master process will now write all Numerov ratio matrices
	// ordered by collision energies on the output file. Notice that only the
	// final ratio matrices at the last R value are written, so to save disk
	// space.
	//

	if (mpi.rank() == mpi::MASTER_PROCESS_RANK) {
		mut<usize> count = 0;

		solution.write(numerov::MAGIC_NUMBER);
		solution.write(FORMAT_VERSION);
		solution.write(channel_count);
		solution.write(mass);
		solution.write(R_list.max);
		solution.write(R_list.max);
		solution.write(R_list.step);
		solution.write(energy_list);

		for (mut<u32> rank = 0; rank < mpi.world_size(); ++rank) {
			for (mut<usize> task = 0; task < (chunk_count - 1); ++task) {
				mut<usize> energy_index = list(rank, task).dereference<usize>(1);

				if (energy_index != count) {
					// NOTE: This is a logic error in the MPI communication and can never happen.
					print::error(WHERE, "Unexpected energy index ", count, "/", chunk_count, " for process ", rank, ": ", energy_index);
				}

				solution.write(list(rank, task));
				++count;
			}
		}

		//
		// Step 4: The remainder energies, if any, are only written after, so to
		// have all energies sorted in ascending order.
		//

		usize extra_task = chunk_count - 1;

		for (mut<u32> rank = 0; rank < mpi.world_size(); ++rank) {
			mut<usize> energy_index = list(rank, extra_task).dereference<usize>(1);

			if (energy_index == 0) {
				// NOTE: Remainder task indices can be zero, meaning that they
				// are unused and outside the energy grid. All work is done at
				// the first occurrence.
				break;
			}

			solution.write(list(rank, extra_task));
			++count;
		}

		// NOTE: Just a sanity check.
		assert(energy_list.count() == count);
	}

	return EXIT_SUCCESS;
}
