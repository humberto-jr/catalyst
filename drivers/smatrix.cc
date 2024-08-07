#include "modules/essentials.h"
#include "modules/numerov.h"
#include "modules/input.h"
#include "modules/file.h"
#include "modules/fgh.h"
#include "key.h"

constexpr u8 PAD = 24;
constexpr u8 FORMAT_VERSION = 3;

struct job {
	mat<f64> k;
	mat<f64> re_s;
	mat<f64> im_s;
	mut<f64> tot_energy;
};

numerov::basis load_scatt_basis(const string &filename)
{
	file::input input(filename.as_cstr());

	u32 count = fgh::is_valid(input);

	numerov::basis list(count);

	fgh::load_basis(0, input, list[0]);

	for (mut<u32> n = 1; n < count; ++n) {
		fgh::load_basis(n, input, list[n]);

		assert(list[n].n_min  == list[n - 1].n_min);
		assert(list[n].r_min  == list[n - 1].r_min);
		assert(list[n].r_max  == list[n - 1].r_max);
		assert(list[n].r_step == list[n - 1].r_step);
	}

	return list;
}

int main()
{
	lapack::frontend lapack;

	//
	// S-matrix output:
	//

	string bufname = input::keyword(key::smatrix_output_filename, "smatrix.bin");

	file::output smatrix(bufname);

	smatrix.write(numerov::MAGIC_NUMBER);
	smatrix.write(FORMAT_VERSION);

	//
	// Numerov ratio matrices:
	//

	bufname = input::keyword(key::smatrix_input_filename);

	numerov::solution solution = numerov::open_ratio_file(bufname);

	u32 channel_count = as_u32(solution[0].rows());

	//
	// Scattering basis set:
	//

	bufname = input::keyword(key::basis_input_filename);

	const numerov::basis basis = load_scatt_basis(bufname);

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
	print::line("# Note: grep -A ", energy_count + 1, " \"# (Ch. = $1\" $filename | grep -A ", energy_count + 1, " \"> (Ch. = $2\"");
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
		                                               ratio, basis, k, lapack);

		mat<f64> re_s(open_count, open_count), im_s(open_count, open_count);

		numerov::build_scatt_matrix(k, re_s, im_s, lapack);

		task[n].k.swap(k);
		task[n].re_s.swap(re_s);
		task[n].im_s.swap(im_s);

		// NOTE: We copy the total energy to avoid streaming it from the disk again later.
		task[n].tot_energy = solution.energy;
	}

	//
	// Step 2: Sort the result per a-->b transitions and print as a function of energy.
	//

	smatrix.write(channel_count);
	smatrix.write(energy_count);

	for (mut<u32> ch_a = 0; ch_a < channel_count; ++ch_a) {
		for (mut<u32> ch_b = ch_a; ch_b < channel_count; ++ch_b) {
			smatrix.write(ch_a);
			smatrix.write(ch_b);

			smatrix.write(basis[ch_a].j);
			smatrix.write(basis[ch_a].v);
			smatrix.write(basis[ch_a].J);
			smatrix.write(basis[ch_a].l);
			smatrix.write(basis[ch_a].p);
			smatrix.write(basis[ch_a].comp);

			smatrix.write(basis[ch_b].j);
			smatrix.write(basis[ch_b].v);
			smatrix.write(basis[ch_b].J);
			smatrix.write(basis[ch_b].l);
			smatrix.write(basis[ch_b].p);
			smatrix.write(basis[ch_b].comp);

			for (mut<u32> n = 0; n < energy_count; ++n) {
				smatrix.write(n);

				usize open_count = task[n].re_s.rows();

				if ((ch_a >= open_count) || (ch_b >= open_count)) {
					// NOTE: Assuming energies and basis are sorted in ascending
					// order, if the entrance channel 'a' or exit channel 'b' is
					// closed at the n-th energy, they may be open at energies
					// n+1, n+2, etc.

					smatrix.write(0.0);
					smatrix.write(0.0);
					smatrix.write(0.0);
					smatrix.write(0.0);
					smatrix.write(0.0);
					continue;
				}

				// NOTE: A last sanity check to make sure the channels are indeed open.
				// If this ever fails, then numerov::build_react_matrix() is counting
				// open channels incorrectly.
				assert(task[n].tot_energy > basis[ch_a].eigenval);
				assert(task[n].tot_energy > basis[ch_b].eigenval);

				f64 wavenum_a = std::sqrt(2.0*solution.mass*(task[n].tot_energy - basis[ch_a].eigenval));
				f64 wavenum_b = std::sqrt(2.0*solution.mass*(task[n].tot_energy - basis[ch_b].eigenval));

				smatrix.write(wavenum_a);
				smatrix.write(wavenum_b);
				smatrix.write(task[n].tot_energy);
				smatrix.write(task[n].re_s(ch_a, ch_b));
				smatrix.write(task[n].im_s(ch_a, ch_b));

				if (n == 0) {
					print::line("# (",
					            "Ch. = ", ch_a,
					            ", v = ", basis[ch_a].v,
					            ", j = ", basis[ch_a].j,
					            ", l = ", basis[ch_a].l,
					            ", J = ", basis[ch_a].J,
					            ", eigenvalue = ", (basis[ch_a].eigenval + shift)*scale,
					            ") --> (",
					            "Ch. = ", ch_b,
					            ", v' = ", basis[ch_b].v,
					            ", j' = ", basis[ch_b].j,
					            ", l' = ", basis[ch_b].l,
					            ", J' = ", basis[ch_b].J,
					            ", eigenvalue = ", (basis[ch_b].eigenval + shift)*scale, ')');

					print::line<PAD>("# Col. energy", "Tot. energy", "k (a.u.)", "k' (a.u.)", "|S|^2", "re(S)", "im(S)", "K (open-open block)");
				}

				f64 k = task[n].k(ch_a, ch_b);

				c64 s = c64(task[n].re_s(ch_a, ch_b), task[n].im_s(ch_a, ch_b));

				f64 tot_energy = (task[n].tot_energy + shift)*scale;

				f64 col_energy = (task[n].tot_energy - basis[ch_a].eigenval + shift)*scale;

				print::line<PAD>(col_energy, tot_energy, wavenum_a, wavenum_b, std::abs(s*s), s.real(), s.imag(), k);
			}

			print::line();
		}
	}

	return EXIT_SUCCESS;
}
