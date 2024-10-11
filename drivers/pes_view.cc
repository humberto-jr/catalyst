#include "modules/essentials.h"
#include "modules/input.h"
#include "modules/pes.h"
#include "key.h"

constexpr u8 PAD = 4;

int main()
{
	//
	// Vibrational grid, r:
	//

	u32 n_min = input::keyword(key::rovib_grid_start, 0u, u32_max, 0u);

	u32 r_count = input::keyword(key::rovib_grid_size, 1u, u32_max, 100u);

	f64 r_min = input::keyword(key::r_min, 0.0, f64_max, 0.5);

	f64 r_max = input::keyword(key::r_max, r_min, f64_max, r_min + 100.0);

	f64 r_step = (r_max - r_min)/as_f64(r_count);

	//
	// Scattering grid, R:
	//

	u32 m_min = input::keyword(key::scatt_grid_start, 0u, u32_max, 0u);

	u32 R_count = input::keyword(key::scatt_grid_size, 1u, u32_max, 100u);

	f64 R_min = input::keyword(key::R_min, 0.0, f64_max, 0.5);

	f64 R_max = input::keyword(key::R_max, R_min, f64_max, R_min + 100.0);

	f64 R_step = (R_max - R_min)/as_f64(R_count);

	//
	// Angular grid, theta:
	//

	u32 p_min = input::keyword(key::theta_grid_start, 0u, u32_max, 0u);

	u32 theta_count = input::keyword(key::theta_grid_size, 1u, u32_max, 181u);

	f64 theta_min = input::keyword(key::theta_min, 0.0, 180.0, 0.0);

	f64 theta_max = input::keyword(key::theta_max, theta_min, 180.0, 180.0);

	f64 theta_step = (theta_max - theta_min)/as_f64(theta_count);

	//
	// Rotational quantum number, j:
	//

	u32 j_min = input::keyword(key::j_min, 0u, u32_max, 0u);

	u32 j_max = input::keyword(key::j_max, j_min, u32_max, j_min);

	u32 j_step = input::keyword(key::j_step, 1u, u32_max, 1u);

	//
	// Legendre multipole expansion, lambda:
	//

	u32 lambda_min = input::keyword(key::lambda_min, 0u, u32_max, 0u);

	u32 lambda_max = input::keyword(key::lambda_max, lambda_min, u32_max, lambda_min + 20u);

	u32 lambda_step = input::keyword(key::lambda_step, 0u, u32_max, 0u);

	//
	// Atomic masses and arrangement (a = 1, b = 2, c = 3):
	//

	const char arrang = as_char(96 + input::keyword(key::arrangement, 1, 3, 1));

	const auto atom_a = input::keyword(key::atom_a, nist::Isotope::atom_unknown);
	const auto atom_b = input::keyword(key::atom_b, nist::Isotope::atom_unknown);
	const auto atom_c = input::keyword(key::atom_c, nist::Isotope::atom_unknown);

	//
	// PES:
	//

	const String pesname = input::keyword(key::extern_pes_filename);

	pes::Frontend pes(pesname, atom_a, atom_b, atom_c);

	//
	// Energy scale and shift:
	//

	f64 shift = input::keyword(key::energy_shift, -f64_max, f64_max, 0.0);

	f64 scale = input::keyword(key::energy_scale, -f64_max, f64_max, 1.0);

	//
	// Summary:
	//

	print::timestamp();
	print::line("# Atom a: ", pes.atom_a());
	print::line("# Atom b: ", pes.atom_b());
	print::line("# Atom c: ", pes.atom_c());
	print::line("# ArRangement: ", arrang);
	print::line("# Shift: ", shift);
	print::line("# Scale: ", scale);
	print::line("# PES shared library: ", pes.filename());

	if ((lambda_step > 0) && (shift != 0.0)) {
		print::line("# WARNING: Printing Legendre multipoles with a shift applied.");
	}

	//
	// Theta-only print:
	//

	if ((lambda_step == 0) && (r_step == 0.0) && (R_step == 0.0) && (theta_step > 0.0)) {
		for (mut<u32> p = 0; p < theta_count; ++p) {
			f64 theta = theta_min + as_f64(p_min + p)*theta_step;

			f64 v = pes.value(arrang, r_min, R_min, theta);

			print::line<PAD>(theta, ' ', (v + shift)*scale);
		}
	}

	//
	// R-only print:
	//

	else if ((lambda_step == 0) && (r_step == 0.0) && (R_step > 0.0) && (theta_step == 0.0)) {
		for (mut<u32> m = 0; m < R_count; ++m) {
			f64 R = R_min + as_f64(m_min + m)*R_step;

			f64 v = pes.value(arrang, r_min, R, theta_min);

			print::line<PAD>(R, ' ', (v + shift)*scale);
		}
	}

	//
	// r-only print (with rot. barrier):
	//

	else if ((lambda_step == 0) && (r_step > 0.0) && (R_step == 0.0) && (theta_step == 0.0)) {
		for (mut<u32> j = j_min; j <= j_max; j += j_step) {
			print::line("# j = ", j);

			for (mut<u32> n = 0; n < r_count; ++n) {
				f64 r = r_min + as_f64(n_min + n)*r_step;

				mut<f64> v = 0.0;

				switch (arrang) {
					case 'a': v = pes.diatom_bc(j, r); break;
					case 'b': v = pes.diatom_ac(j, r); break;
					case 'c': v = pes.diatom_ab(j, r); break;
				}

				print::line<PAD>(r, ' ', (v + shift)*scale);
			}

			print::line();
		}
	}

	//
	// (R, theta) print:
	//

	else if ((lambda_step == 0) && (r_step == 0.0) && (R_step > 0.0) && (theta_step > 0.0)) {
		for (mut<u32> m = 0; m < R_count; ++m) {
			f64 R = R_min + as_f64(m_min + m)*R_step;

			for (mut<u32> p = 0; p < theta_count; ++p) {
				f64 theta = theta_min + as_f64(p_min + p)*theta_step;

				f64 v = pes.value(arrang, r_min, R, theta);

				print::line<PAD>(R, ' ', theta, ' ', (v + shift)*scale);
			}

			print::line();
		}
	}

	//
	// (r, theta) print:
	//

	else if ((lambda_step == 0) && (r_step > 0.0) && (R_step == 0.0) && (theta_step > 0.0)) {
		for (mut<u32> n = 0; n < r_count; ++n) {
			f64 r = r_min + as_f64(n_min + n)*r_step;

			for (mut<u32> p = 0; p < theta_count; ++p) {
				f64 theta = theta_min + as_f64(p_min + p)*theta_step;

				f64 v = pes.value(arrang, r, R_min, theta);

				print::line<PAD>(r, ' ', theta, ' ', (v + shift)*scale);
			}

			print::line();
		}
	}

	//
	// (r, R) print:
	//

	else if ((lambda_step == 0) && (r_step > 0.0) && (R_step > 0.0) && (theta_step == 0.0)) {
		for (mut<u32> n = 0; n < r_count; ++n) {
			f64 r = r_min + as_f64(n_min + n)*r_step;

			for (mut<u32> m = 0; m < R_count; ++m) {
				f64 R = R_min + as_f64(m_min + m)*R_step;

				f64 v = pes.value(arrang, r, R, theta_min);

				print::line<PAD>(r, ' ', R, ' ', (v + shift)*scale);
			}

			print::line();
		}
	}

	//
	// Legendre multipoles print:
	//

	else if (lambda_step > 0) {
		for (mut<u32> lambda = lambda_min; lambda <= lambda_max; lambda += lambda_step) {
			for (mut<u32> n = 0; n < r_count; ++n) {
				f64 r = r_min + as_f64(n_min + n)*r_step;

				print::line("# lambda = ", lambda, ", r = ", r);

				for (mut<u32> m = 0; m < R_count; ++m) {
					f64 R = R_min + as_f64(m_min + m)*R_step;

					f64 v = pes.legendre_multipole_term(arrang, lambda, r, R);

					print::line<PAD>(R, ' ', (v + shift)*scale);
				}

				print::line();
			}
		}
	}

	//
	// (r, R, theta) print:
	//

	else {
		for (mut<u32> n = 0; n < r_count; ++n) {
			f64 r = r_min + as_f64(n_min + n)*r_step;

			for (mut<u32> m = 0; m < R_count; ++m) {
				f64 R = R_min + as_f64(m_min + m)*R_step;

				for (mut<u32> p = 0; p <= theta_count; ++p) {
					f64 theta = theta_min + as_f64(p_min + p)*theta_step;

					f64 v = pes.value(arrang, r, R, theta);

					print::line<PAD>(r, ' ', R, ' ', theta, ' ', (v + shift)*scale);
				}

				print::line();
			}

			print::line();
		}
	}

	return EXIT_SUCCESS;
}
