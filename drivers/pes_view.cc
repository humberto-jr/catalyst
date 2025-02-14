#include "modules/essentials.h"
#include "user.h"

#define SHIFT_AND_SCALE(val) (((val) + shift)*scale)

constexpr u8 PAD = 24;

int main()
{
	//
	// (r, R, theta)-grid:
	//

	const Range<f64> r_list = user::vibration_grid();

	const Range<f64> R_list = user::scattering_grid();

	const Range<f64> theta_list = user::polar_angle_grid();

	//
	// Diatomic rotation quantum numbers:
	//

	const Range<u32> j_list = user::rotation_quantum_numbers();

	//
	// Arrangement (a = 1, b = 2, c = 3) and PES:
	//

	const char arrang = user::arrangement();

	pes::Frontend pes = user::extern_pes();

	const Range<u32> lambda_list = user::multipole_terms(0u);

	//
	// Energy scale and shift:
	//

	f64 shift = user::energy_shift();
	f64 scale = user::energy_scale();

	//
	// Summary:
	//

	print::timestamp();
	print::line("# Atom a: ", pes.atom_a());
	print::line("# Atom b: ", pes.atom_b());
	print::line("# Atom c: ", pes.atom_c());
	print::line("# Arrangement: ", arrang);
	print::line("# Energy shift: ", shift);
	print::line("# Energy scale: ", scale);
	print::line("# PES shared library: ", pes.filename());

	if ((lambda_list.count() > 0) && (shift != 0.0)) {
		print::line("# WARNING: Printing Legendre multipoles with a shift applied");
	}

	//
	// Theta-only printing:
	//

	if ((lambda_list.count() == 0) && (r_list.count() == 0) && (R_list.count() == 0) && (theta_list.count() > 0)) {
		print::line<PAD>("# theta", "PES");

		for (f64 theta : theta_list.as_range_inclusive()) {
			f64 v = pes.value(arrang, r_list.min, R_list.min, theta);

			print::line<PAD>(theta, SHIFT_AND_SCALE(v));
		}
	}

	//
	// R-only printing:
	//

	else if ((lambda_list.count() == 0) && (r_list.count() == 0) && (R_list.count() > 0) && (theta_list.count() == 0)) {
		print::line<PAD>("# R (a.u.)", "PES");

		for (f64 R : R_list) {
			f64 v = pes.value(arrang, r_list.min, R, theta_list.min);

			print::line<PAD>(R, SHIFT_AND_SCALE(v));
		}
	}

	//
	// r-only printing (with j-dependent centrifugal barrier):
	//

	else if ((lambda_list.count() == 0) && (r_list.count() > 0) && (R_list.count() == 0) && (theta_list.count() == 0)) {
		for (u32 j : j_list) {
			print::line("# j = ", j);
			print::line<PAD>("# r (a.u.)", "PES");

			for (f64 r : r_list) {
				mut<f64> v = 0.0;

				switch (arrang) {
					case 'a': v = pes.diatom_bc(j, r); break;
					case 'b': v = pes.diatom_ac(j, r); break;
					case 'c': v = pes.diatom_ab(j, r); break;
				}

				print::line<PAD>(r, SHIFT_AND_SCALE(v));
			}

			print::line();
		}
	}

	//
	// (R, theta) printing:
	//

	else if ((lambda_list.count() == 0) && (r_list.count() == 0) && (R_list.count() > 0) && (theta_list.count() > 0)) {
		print::line<PAD>("# R (a.u.)", "theta", "PES");

		for (f64 R : R_list) {
			for (f64 theta : theta_list.as_range_inclusive()) {
				f64 v = pes.value(arrang, r_list.min, R, theta);

				print::line<PAD>(R, theta, SHIFT_AND_SCALE(v));
			}

			print::line();
		}
	}

	//
	// (r, theta) printing:
	//

	else if ((lambda_list.count() == 0) && (r_list.count() > 0) && (R_list.count() == 0) && (theta_list.count() > 0)) {
		print::line<PAD>("# r (a.u.)", "theta", "PES");

		for (f64 r : r_list) {
			for (f64 theta : theta_list.as_range_inclusive()) {
				f64 v = pes.value(arrang, r, R_list.min, theta);

				print::line<PAD>(r, theta, SHIFT_AND_SCALE(v));
			}

			print::line();
		}
	}

	//
	// (r, R) printing:
	//

	else if ((lambda_list.count() == 0) && (r_list.count() > 0) && (R_list.count() > 0) && (theta_list.count() == 0)) {
		print::line<PAD>("# r (a.u.)", "R (a.u.)", "PES");

		for (f64 r : r_list) {
			for (f64 R : R_list) {
				f64 v = pes.value(arrang, r, R, theta_list.min);

				print::line<PAD>(r, R, SHIFT_AND_SCALE(v));
			}

			print::line();
		}
	}

	//
	// Legendre multipole printing:
	//

	else if (lambda_list.count() > 0) {
		for (u32 lambda : lambda_list.as_range_inclusive()) {
			for (f64 r : r_list) {
				print::line("# lambda = ", lambda, ", r = ", r, " a.u.");
				print::line<PAD>("# R (a.u.)", "PES");

				for (f64 R : R_list) {
					f64 v = pes.legendre_multipole_term(arrang, lambda, r, R);

					print::line<PAD>(R, SHIFT_AND_SCALE(v));
				}

				print::line();
			}
		}
	}

	//
	// (r, R, theta) printing:
	//

	else {
		print::line<PAD>("# r (a.u.)", "R (a.u.)", "theta", "PES");

		for (f64 r : r_list) {
			for (f64 R : R_list) {
				for (f64 theta : theta_list.as_range_inclusive()) {
					f64 v = pes.value(arrang, r, R, theta);

					print::line<PAD>(r, R, theta, SHIFT_AND_SCALE(v));
				}

				print::line();
			}

			print::line();
		}
	}

	return EXIT_SUCCESS;
}
