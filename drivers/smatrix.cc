#include "modules/essentials.h"
#include "modules/numerov.h"
#include "modules/input.h"
#include "modules/file.h"
#include "modules/fgh.h"

// Internals
#include "filename.h"
#include "key.h"

constexpr u8 PAD = 24;
constexpr u8 FORMAT_VERSION = 3;

struct job {
	mat<f64> k;
	mat<f64> re_s;
	mat<f64> im_s;
	mut<f64> total_energy;
};

int main()
{
	//
	// S-matrix output:
	//

	string bufname = input::keyword(key::smatrix_output_filename, filename::smatrix);

	file::output smatrix(bufname);

	//
	// Numerov ratio matrices:
	//

	bufname = input::keyword(key::smatrix_input_filename, filename::ratio_matrix);

	auto solution = numerov::open_ratio_file(bufname);

	u32 channel_count = as_u32(solution[0].rows());

	//
	// Scattering basis set:
	//

	bufname = input::keyword(key::basis_input_filename, filename::fgh_basis);

	const auto basis = numerov::open_basis_file(bufname);

	//
	// Collision energy:
	//

	u32 energy_count = as_u32((solution.E_max - solution.E_min)/solution.E_step);

	f64 shift = input::keyword(key::energy_shift, -f64_max, f64_max, 0.0);

	f64 scale = input::keyword(key::energy_scale, -f64_max, f64_max, 1.0);

	//
	// Summary:
	//

	print::timestamp();
	print::line("# Num. of channels: ", channel_count);
	print::line("# Num. of energies: ", energy_count);
	print::line("# Energy shift: ", shift);
	print::line("# Energy scale: ", scale);
	print::line("# Reduced mass: ", solution.mass, " a.u.");
	print::line("# Output file: ", smatrix.filename.as_cstr());
	print::line("# Scatt. basis: ", bufname.as_cstr());
	print::line("# Numerov solutions: ", solution.input.filename.as_cstr());
	print::line("# Note: grep -A ", energy_count + 1, " \"# (Ch. = $1,\" $filename | grep -A ", energy_count + 1, " \"> (Ch. = $2,\"");
	print::line("#");

	//
	// Step 1: Compute the augmented K-matrix and S-matrix for every energy.
	//

	vec<job> task(energy_count);

	for (mut<u32> n = 0; n < energy_count; ++n) {
		const mat<f64> &ratio = solution[n];

		mat<f64> k(channel_count, channel_count);

		usize open_count = numerov::build_react_matrix(solution.mass,
		                                               solution.R_step,
		                                               solution.R_max,
		                                               solution.energy,
		                                               ratio, basis, k);

		mat<f64> re_s(open_count, open_count), im_s(open_count, open_count);

		if (open_count > 0) {
			k.resize(open_count, open_count);
			numerov::build_scatt_matrix(k, re_s, im_s);
		}

		task[n].k.swap(k);
		task[n].re_s.swap(re_s);
		task[n].im_s.swap(im_s);

		// NOTE: We copy the total energy to avoid streaming it from the disk again later.
		task[n].total_energy = solution.energy;
	}

	//
	// Step 2: Sort the result per a-->b transitions and print as a function of energy.
	//

	smatrix.write(numerov::MAGIC_NUMBER);
	smatrix.write(FORMAT_VERSION);
	smatrix.write(channel_count);
	smatrix.write(energy_count);
	smatrix.write(solution.mass);

	for (mut<u32> channel_a = 0; channel_a < channel_count; ++channel_a) {
		for (mut<u32> channel_b = 0; channel_b < channel_count; ++channel_b) {
			bool was_closed = true;

			// NOTE: (x12 u32, 48 bytes) + (x2 s32, 8 bytes) + (x2 f64, 16 bytes).
			// It gives a total of 72 initial bytes for each pair of channels, ab.

			smatrix.write(channel_a);
			smatrix.write(channel_b);

			smatrix.write(basis[channel_a].j);
			smatrix.write(basis[channel_a].v);
			smatrix.write(basis[channel_a].J);
			smatrix.write(basis[channel_a].l);
			smatrix.write(basis[channel_a].p);
			smatrix.write(basis[channel_a].comp);
			smatrix.write(basis[channel_a].eigenval);

			smatrix.write(basis[channel_b].j);
			smatrix.write(basis[channel_b].v);
			smatrix.write(basis[channel_b].J);
			smatrix.write(basis[channel_b].l);
			smatrix.write(basis[channel_b].p);
			smatrix.write(basis[channel_b].comp);
			smatrix.write(basis[channel_b].eigenval);

			// NOTE: Shifted and/or scaled energies are for printing. Only the
			// original values in atomic units are written to binary files.
			f64 eigenval_a = (basis[channel_a].eigenval + shift)*scale;
			f64 eigenval_b = (basis[channel_b].eigenval + shift)*scale;

			for (mut<u32> n = 0; n < energy_count; ++n) {
				f64 total_energy = (task[n].total_energy + shift)*scale;

				// NOTE: (x1 u32, 4 bytes) + (x3 f64, 24 bytes).
				// For each chunk of 72 bytes, we add more energy_count*28 bytes.

				smatrix.write(n);
				smatrix.write(task[n].total_energy);

				if ((total_energy > eigenval_a) && (total_energy > eigenval_b)) {
					smatrix.write(task[n].re_s(channel_a, channel_b));
					smatrix.write(task[n].im_s(channel_a, channel_b));
				} else {
					smatrix.write(0.0);
					smatrix.write(0.0);
					continue;
				}

				smatrix.write(task[n].re_s(channel_a, channel_b));
				smatrix.write(task[n].im_s(channel_a, channel_b));

				if (was_closed) {
					print::line("# (",
					            "Ch. = ", channel_a,
					            ", v = ", basis[channel_a].v,
					            ", j = ", basis[channel_a].j,
					            ", l = ", basis[channel_a].l,
					            ", J = ", basis[channel_a].J,
					            ", eigenvalue = ", eigenval_a,
					            ") --> (",
					            "Ch. = ", channel_b,
					            ", v' = ", basis[channel_b].v,
					            ", j' = ", basis[channel_b].j,
					            ", l' = ", basis[channel_b].l,
					            ", J' = ", basis[channel_b].J,
					            ", eigenvalue = ", eigenval_b, ')');

					print::line<PAD>("# Coll. energy", "Tot. energy", "k (a.u.)", "k' (a.u.)", "|S|^2", "re(S)", "im(S)", "K (open-open block)");
					was_closed = false;
				}

				f64 k = task[n].k(channel_a, channel_b);

				c64 s = c64(task[n].re_s(channel_a, channel_b), task[n].im_s(channel_a, channel_b));

				f64 wavenum_a = std::sqrt(2.0*solution.mass*(task[n].total_energy - basis[channel_a].eigenval));

				f64 wavenum_b = std::sqrt(2.0*solution.mass*(task[n].total_energy - basis[channel_b].eigenval));

				print::line<PAD>(total_energy - eigenval_a, total_energy, wavenum_a, wavenum_b, std::abs(s*s), s.real(), s.imag(), k);
			}

			print::line();
		}
	}

	return EXIT_SUCCESS;
}
