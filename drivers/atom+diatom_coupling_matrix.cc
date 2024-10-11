#include "modules/essentials.h"
#include "modules/numerov.h"
#include "modules/libmpi.h"
#include "modules/input.h"
#include "modules/timer.h"
#include "modules/math.h"
#include "modules/file.h"
#include "modules/pes.h"
#include "modules/fgh.h"

// Internals
#include "filename.h"
#include "key.h"

// NOTE: Older GNU compilers appears to have used an OpenMP version in which constant objects
// are shared by default and not required in the shared clause, even if default(none) is used.
// Later versions seem to require. The behavior, however, was not consistent between GNU g++
// and LLVM clang++. Here, we define the shared list in advance based on the compiler used.
// Search for "_Pragma(OMP_PARALLEL_LOOP)" to see where this takes place below (only one loop).
#if defined(USING_GNU_COMPILER) && (__GNUC__ < 9)
	#define OMP_PARALLEL_LOOP "omp parallel for default(none) shared(lambda, multipole, result) schedule(static) if(use_omp)"
#else
	#define OMP_PARALLEL_LOOP "omp parallel for default(none) shared(mass, R, lambda_min, lambda, basis, multipole, result) schedule(static) if(use_omp)"
#endif

constexpr u8 FORMAT_VERSION = 1;

f64 simpson(const Vec<f64> &multipole, const fgh::Basis &basis_a, const fgh::Basis &basis_b)
{
	mut<usize> n_max = basis_a.eigenvec.length() - 1;

	f64 step = basis_a.r_step;

	f64 fact = 3.0/8.0;

	while (n_max%3 != 0) {
		--n_max;
	}

	assert(n_max > 2);

	mut<f64> sum = basis_a[0]*multipole[0]*basis_b[0];

	for (mut<usize> n = 1; n < (n_max - 3); n += 3) {
		// NOTE: Integral <a|V|b> using Simpson's 3/8 rule.
		sum += 3.0*basis_a[n + 0]*multipole[n + 0]*basis_b[n + 0];
		sum += 3.0*basis_a[n + 1]*multipole[n + 1]*basis_b[n + 1];
		sum += 2.0*basis_a[n + 2]*multipole[n + 2]*basis_b[n + 2];
	}

	sum += 3.0*basis_a[n_max - 1]*multipole[n_max - 1]*basis_b[n_max - 1];

	sum += basis_a[n_max]*multipole[n_max]*basis_b[n_max];

	return fact*step*sum;
}

int main(int argc, char *argv[])
{
	mpi::Frontend mpi(&argc, &argv);

	//
	// Scattering grid:
	//

	u32 n_min = mpi.input_keyword(key::scatt_grid_start, 0u, u32_max, 0u);

	u32 R_count = mpi.input_keyword(key::scatt_grid_size, 1u, u32_max, 100u);

	f64 R_min = mpi.input_keyword(key::R_min, 0.0, f64_max, 0.5);

	f64 R_max = mpi.input_keyword(key::R_max, R_min, f64_max, R_min + 100.0);

	f64 R_step = (R_max - R_min)/as_f64(R_count);

	mpi.set_tasks(R_count);

	//
	// Legendre multipole expansion terms:
	//

	u32 lambda_min = mpi.input_keyword(key::lambda_min, 0u, u32_max, 0u);

	u32 lambda_max = mpi.input_keyword(key::lambda_max, lambda_min, u32_max, lambda_min + 20u);

	u32 lambda_step = mpi.input_keyword(key::lambda_step, 1u, u32_max, 2u);

	//
	// Isotopes and arrangement (a = 1, b = 2, c = 3):
	//

	const char arrang = as_char(96 + mpi.input_keyword(key::arrangement, 1, 3, 1));

	if ((arrang != 'a') && (arrang != 'b') && (arrang != 'c')) {
		print::error(WHERE, "Invalid arrangement ", arrang);
	}

	const auto atom_a = mpi.input_keyword(key::atom_a, nist::Isotope::atom_unknown);
	const auto atom_b = mpi.input_keyword(key::atom_b, nist::Isotope::atom_unknown);
	const auto atom_c = mpi.input_keyword(key::atom_c, nist::Isotope::atom_unknown);

	//
	// PES:
	//

	const String pesname = mpi.input_keyword(key::extern_pes_filename);

	pes::Frontend pes(pesname, atom_a, atom_b, atom_c);

	f64 mass = pes.mass_abc(arrang);

	//
	// Scattering basis set:
	//

	String bufname = mpi.input_keyword(key::basis_input_filename, filename::fgh_basis);

	const auto basis = numerov::open_basis_file(bufname);

	Vec<f64> multipole(basis[0].eigenvec.length());

	Mat<f64> result(basis.length(), basis.length());

	//
	// Output: Open on the master process only. Other processes will write to
	// temporary *.mpi* files, and their content will be sorted and included
	// in the master's output at the end.
	//

	bufname = mpi.input_keyword(key::coupling_output_filename, filename::coupling_matrix);

	if (mpi.rank() != mpi::MASTER_PROCESS_RANK) {
		bufname.append(".mpi", mpi.rank());
	}

	file::Output coupling(bufname.as_cstr());

	//
	// OpenMP:
	//

	const bool use_omp = mpi.input_keyword(key::use_omp, false);

	//
	// Summary:
	//

	if (mpi.rank() == mpi::MASTER_PROCESS_RANK) {
		coupling.write(numerov::MAGIC_NUMBER);
		coupling.write(FORMAT_VERSION);
		coupling.write(n_min);
		coupling.write(R_min);
		coupling.write(R_max);
		coupling.write(R_step);
		coupling.write(mass);
		coupling.write(basis.length());

		print::timestamp();
		print::line("# Atom a: ", pes.atom_a());
		print::line("# Atom b: ", pes.atom_b());
		print::line("# Atom c: ", pes.atom_c());
		print::line("# Arrangement: ", arrang);
		print::line("# MPI procs.: ", mpi.world_size());
		print::line("# Using OpenMP: ", (use_omp? "yes" : "no"));
		print::line("# Lambda range: ", lambda_min, ", ", lambda_max, ", ", lambda_step);
		print::line("# Disk output: ", coupling.filename.as_cstr());
		print::line("# PES shared library: ", pes.filename());
		print::line("# Atom-diatom reduc. mass: ", mass, " a.u.");
		print::line("#");
		print::line("#  Proc.        R (a.u.)           time (s)");
		print::line("# -------------------------------------------");
	}

	//
	// Build the atom-diatom coupling matrix for all values of R:
	//

	for (mut<u32> n = mpi.first_local_task(); n <= mpi.last_local_task(); ++n) {
		extra_step:
		f64 R = R_min + as_f64(n_min + n)*R_step;

		result = 0.0;

		Timer<1> clock;
		clock.start();

		for (mut<u32> lambda = lambda_min; lambda <= lambda_max; lambda += lambda_step) {

			// NOTE: Assuming that r_min and r_step are the same for all basis functions.
			pes.legendre_multipole_term(arrang, lambda, basis[0].n_min, basis[0].r_min, basis[0].r_step, R, multipole);

			_Pragma(OMP_PARALLEL_LOOP)
			for (mut<usize> ch_a = 0; ch_a < result.rows(); ++ch_a) {
				u32 Ja = basis[ch_a].J;
				u32 ja = basis[ch_a].j;
				u32 la = basis[ch_a].l;

				for (mut<usize> ch_b = ch_a; ch_b < result.cols(); ++ch_b) {
					u32 Jb = basis[ch_b].J;
					u32 jb = basis[ch_b].j;
					u32 lb = basis[ch_b].l;

					if (Ja != Jb) {
						continue;
					}

					if ((lambda == lambda_min) && (ch_a == ch_b)) {
						result(ch_a, ch_a) += basis[ch_a].eigenval + numerov::centrifugal_term(la, mass, R);
					}

					f64 f = math::percival_seaton_coeff(Ja, ja, jb, la, lb, lambda);

					if (f == 0.0) {
						continue;
					}

					// NOTE: Each thread will work on a unique pair of channels, ab.
					// Thus, there are no race conditions on access to the result matrix.

					result(ch_a, ch_b) += f*simpson(multipole, basis[ch_a], basis[ch_b]);
					result(ch_b, ch_a) = result(ch_a, ch_b);
				}
			}
		}

		clock.stop();

		coupling.write(n);
		coupling.write(R);
		coupling.write(result);

		print::line<7>(mpi.rank(), ' ', as_f32(R), ' ', as_f32(clock[0]));

		if (n == mpi.last_local_task()) {
			auto index = mpi.extra_task();

			if (index.has_value()) {
				n = index.value();
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
		for (mut<u32> rank = 1; rank < mpi.world_size(); ++rank) {
			bufname.clear();
			bufname.append(coupling.filename.as_cstr(), ".mpi", rank);

			file::Input buf(bufname.as_cstr());

			while (buf.end() == false) {
				mut<u32> n = 0;
				buf.read(n);

				mut<f64> R = 0.0;
				buf.read(R);

				buf.read(result);

				if (n > mpi.last_local_task()) {
					coupling.write(n);
					coupling.write(R);
					coupling.write(result);
				}
			}
		}
	}

	return EXIT_SUCCESS;
}
