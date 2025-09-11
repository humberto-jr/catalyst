#include "modules/essentials.h"
#include "modules/libtoml.h"
#include "modules/numerov.h"
#include "modules/timer.h"
#include "modules/math.h"

// NOTE: Older GNU compilers appears to have used an OpenMP version in which constant objects
// are shared by default and not required in the shared clause, even if default(none) is used.
// Later versions seem to require. However, the behavior is not consistent between GNU g++ and
// LLVM clang++. Here, we define the shared list in advance based on the compiler used. Search
// for "_Pragma(OMP_PARALLEL_LOOP)" to see where this takes place below (only one loop).
#if defined(USING_GNU_COMPILER) && (__GNUC__ < 9)
	#define OMP_PARALLEL_LOOP "omp parallel for default(none) shared(lambda, multipole, result) schedule(static) if(use_omp)"
#else
	#define OMP_PARALLEL_LOOP "omp parallel for default(none) shared(mass, R, lambda_list, lambda, basis, multipole, result) schedule(static) if(use_omp)"
#endif

constexpr u8 FORMAT_VERSION = 1;

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
	// Scattering grid:
	//

	Range<f64> R_list = toml.range("jacobi", "R", 0.5, 100.0, 0.25, &mpi);

	mpi.set_tasks(R_list.count());

	//
	// PES:
	//

	const char arrang = as_char(96 + toml.value("pes", "arrang", 1, 3, 1, &mpi));

	const auto atom_a = toml.isotope("pes", "atom_a", nist::Isotope::atom_unknown, &mpi);

	const auto atom_b = toml.isotope("pes", "atom_b", nist::Isotope::atom_unknown, &mpi);

	const auto atom_c = toml.isotope("pes", "atom_c", nist::Isotope::atom_unknown, &mpi);

	Range<u32> lambda_list = toml.range("pes", "legendre_expansion", 0u, 20u, 1u, &mpi);

	c_str pesname = toml.string("pes", "filename", "\0", &mpi);

	if (pesname[0] == '\0') {
		print::error(WHERE, "Expecting the PES shared library (*.so) at pes.filename");
	}

	pes::Frontend pes(pesname, atom_a, atom_b, atom_c);

	f64 mass = pes.mass_abc(arrang);

	//
	// Scattering basis set:
	//

	String filename = toml.string("fgh", "filename", "atom+diatom_fgh_basis.bin", &mpi);

	const numerov::Basis basis(filename);

	Vec<f64> multipole(basis.list[0].eigenvec.length());

	Mat<f64> result(basis.list.length(), basis.list.length());

	//
	// Output: Open on the master process only. Other processes will write to
	// temporary *.mpi* files, and their content will be sorted and included
	// in the master's output at the end.
	//

	file::Output coupling = toml.output_filename("coupling_matrix", "atom+diatom_coupling_matrix.bin", &mpi);

	//
	// OpenMP:
	//

	const bool use_omp = toml.value("omp", "use", false, &mpi);

	//
	// Summary:
	//

	if (mpi.rank() == mpi::MASTER_PROCESS_RANK) {
		coupling.write(numerov::MAGIC_NUMBER);
		coupling.write(FORMAT_VERSION);
		coupling.write(basis.list.length());
		coupling.write(R_list);
		coupling.write(mass);

		print::line();
		print::line("# Atom-diatom reduced mass: ", mass, " a.u.");
		print::line('#');
		print::line("#    grid        MPI proc.                    R (a.u.)                     time (s)");
		print::line("# ---------------------------------------------------------------------------------");
	}

	//
	// Build the atom-diatom coupling matrix for all values of R:
	//

	for (mut<usize> task = mpi.first_local_task(); task <= mpi.last_local_task(); ++task) {
		extra_step:
		f64 R = R_list[task];

		Timer<1> clock;
		clock.start();

		for (u32 lambda : lambda_list.as_range_inclusive()) {
			pes.legendre_multipole_term(arrang, lambda, basis.list[0].r_list, R, multipole);

			_Pragma(OMP_PARALLEL_LOOP)
			for (mut<usize> channel_a = 0; channel_a < result.rows(); ++channel_a) {

				f64 barrier = basis.list[channel_a].eigenval
				            + numerov::centrifugal_term(basis.list[channel_a].l, mass, R);

				for (mut<usize> channel_b = channel_a; channel_b < result.cols(); ++channel_b) {
					if (lambda == lambda_list.min) {
						result(channel_a, channel_b) = (channel_b == channel_a? barrier : 0.0);

						assert(basis.list[channel_a].spin_mult   == basis.list[channel_b].spin_mult);
						assert(basis.list[channel_a].r_list.min  == basis.list[channel_b].r_list.min);
						assert(basis.list[channel_a].r_list.step == basis.list[channel_b].r_list.step);
					}

					if (basis.list[channel_a].J != basis.list[channel_b].J) {
						continue;
					}

					f64 f = math::percival_seaton_coeff(basis.list[channel_a].J,
					                                    basis.list[channel_a].n,
					                                    basis.list[channel_b].n,
					                                    basis.list[channel_a].j,
					                                    basis.list[channel_b].j,
					                                    basis.list[channel_a].l,
					                                    basis.list[channel_b].l,
					                                    lambda, basis.list[channel_a].spin_mult);
					if (f == 0.0) {
						continue;
					}

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

		print::line<8, '#'>(task, ' ', mpi.rank(), ' ', R, ' ', clock[0]);

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
