#include "modules/essentials.h"
#include "modules/numerov.h"
#include "modules/timer.h"
#include "modules/math.h"
#include "modules/fgh.h"
#include "user.h"

// NOTE: Older GNU compilers appears to have used an OpenMP version in which constant objects
// are shared by default and not required in the shared clause, even if default(none) is used.
// Later versions seem to require. The behavior, however, was not consistent between GNU g++
// and LLVM clang++. Here, we define the shared list in advance based on the compiler used.
// Search for "_Pragma(OMP_PARALLEL_LOOP)" to see where this takes place below (only one loop).
#if defined(USING_GNU_COMPILER) && (__GNUC__ < 9)
	#define OMP_PARALLEL_LOOP "omp parallel for default(none) shared(lambda, multipole, result) schedule(static) if(use_omp)"
#else
	#define OMP_PARALLEL_LOOP "omp parallel for default(none) shared(mass, R, lambda_list, lambda, basis, multipole, result) schedule(static) if(use_omp)"
#endif

constexpr u8 PAD = 24;
constexpr u8 FORMAT_VERSION = 1;

int main(int argc, char *argv[])
{
	mpi::Frontend mpi(&argc, &argv);

	//
	// Scattering grid:
	//

	const Range<f64> R_list = user::scattering_grid(&mpi);

	mpi.set_tasks(R_list.count());

	//
	// Arrangement (a = 1, b = 2, c = 3) and PES:
	//

	const char arrang = user::arrangement(&mpi);

	pes::Frontend pes = user::extern_pes(&mpi);

	f64 mass = pes.mass_abc(arrang);

	//
	// Legendre multipole expansion terms:
	//

	const Range<u32> lambda_list = user::multipole_terms(20u, &mpi);

	//
	// Scattering basis set:
	//

	String filename = user::fgh_basis_input(&mpi);

	const numerov::Basis basis(filename);

	Vec<f64> multipole(basis.list[0].eigenvec.length());

	Mat<f64> result(basis.list.length(), basis.list.length());

	//
	// Output: Open on the master process only. Other processes will write to
	// temporary *.mpi* files, and their content will be sorted and included
	// in the master's output at the end.
	//

	file::Output coupling = user::coupling_output_file(&mpi);

	//
	// OpenMP:
	//

	const bool use_omp = user::use_omp(&mpi);

	//
	// Summary:
	//

	if (mpi.rank() == mpi::MASTER_PROCESS_RANK) {
		coupling.write(numerov::MAGIC_NUMBER);
		coupling.write(FORMAT_VERSION);
		coupling.write(basis.list.length());
		coupling.write(R_list);
		coupling.write(mass);

		print::timestamp();
		print::line("# Atom a: ", pes.atom_a());
		print::line("# Atom b: ", pes.atom_b());
		print::line("# Atom c: ", pes.atom_c());
		print::line("# Arrangement: ", arrang);
		print::line("# MPI procs.: ", mpi.world_size());
		print::line("# Using OpenMP: ", (use_omp? "yes" : "no"));
		print::line("# Basis count: ", basis.list.length());
		print::line("# Lambda range: ", lambda_list.min, ", ", lambda_list.max, ", ", lambda_list.step);
		print::line("# Basis input: ", basis.filename.as_cstr());
		print::line("# Disk output: ", coupling.filename.as_cstr());
		print::line("# PES shared library: ", pes.filename());
		print::line("# Atom-diatom reduc. mass: ", mass, " a.u.");
		print::line('#');
		print::line<PAD>("# proc.", "task", "R (a.u.)", "time (s)");
	}

	//
	// Build the atom-diatom coupling matrix for all values of R:
	//

	for (mut<usize> task = mpi.first_local_task(); task <= mpi.last_local_task(); ++task) {
		extra_step:
		f64 R = R_list[task];

		result = 0.0;

		Timer<1> clock;
		clock.start();

		for (u32 lambda : lambda_list.as_range_inclusive()) {
			// NOTE: Assuming that r_min and r_step are the same for all basis functions.
			pes.legendre_multipole_term(arrang, lambda,
			                            basis.list[0].r_list, R, multipole);

			_Pragma(OMP_PARALLEL_LOOP)
			for (mut<usize> channel_a = 0; channel_a < result.rows(); ++channel_a) {

				f64 rot_term = basis.list[channel_a].eigenval
				             + numerov::centrifugal_term(basis.list[channel_a].l, mass, R);

				for (mut<usize> channel_b = channel_a; channel_b < result.cols(); ++channel_b) {
					if (basis.list[channel_a].J != basis.list[channel_b].J) {
						continue;
					}

					if ((lambda == lambda_list.min) && (channel_b == channel_a)) {
						result(channel_a, channel_a) += rot_term;
					}

					f64 f = math::percival_seaton_coeff(basis.list[channel_a].J,
					                                    basis.list[channel_a].j,
					                                    basis.list[channel_b].j,
					                                    basis.list[channel_a].l,
					                                    basis.list[channel_b].l, lambda);
					if (f == 0.0) {
						continue;
					}

					assert(basis.list[channel_a].r_list.step == basis.list[channel_b].r_list.step);

					f64 overlap_ab = math::simpson(basis.list[channel_a].r_list.step,
					                               multipole,
					                               basis.list[channel_a].eigenvec,
					                               basis.list[channel_b].eigenvec);

					// NOTE: Each thread will work on a unique pair of channels, ab.
					// Thus, there are no race conditions on access to the result matrix.

					result(channel_a, channel_b) += f*overlap_ab;

					if (channel_b != channel_a) {
						result(channel_b, channel_a) = result(channel_a, channel_b);
					}
				}
			}
		}

		clock.stop();

		coupling.write(task);
		coupling.write(R);
		coupling.write(result);

		print::line<PAD>(mpi.rank(), task, R, clock[0]);

		if (task == mpi.last_local_task()) {
			auto index = mpi.extra_task();

			if (index.has_value()) {
				task = index.value();
				goto extra_step;
			}
		}
	}

	//
	// Sorting: If MPI is used, the master process will now open and read all *.mpi*
	// temporary files copying the data, ordered by ranks, to its own output file.
	// If the master arrives here first, it needs to wait so that all processes have
	// finished writing to their temporary files.
	//

	mpi.wait();

	if (mpi.rank() == mpi::MASTER_PROCESS_RANK) {
		filename.resize(2048);

		for (mut<u32> rank = 1; rank < mpi.world_size(); ++rank) {
			filename.clear();
			filename.append(coupling.filename.as_cstr(), ".mpi", rank);

			file::Input input(filename.as_cstr());

			while (input.end() == false) {
				mut<usize> task = 0;
				input.read(task);

				mut<f64> R = 0.0;
				input.read(R);

				input.read(result);

				if (task > mpi.last_local_task()) {
					coupling.write(task);
					coupling.write(R);
					coupling.write(result);
				}
			}
		}
	}

	return EXIT_SUCCESS;
}
