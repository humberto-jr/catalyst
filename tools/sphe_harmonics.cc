#include "modules/essentials.h"
#include "modules/input.h"
#include "modules/math.h"

int main(int argc, char *argv[])
{
	if (argc == 1) {
		print::error("# Usage: ", argv[0], " -l [val] -m [min] [max] -t [size] [min] [max] -p [size] [min] [max]");
	}

	//
	// Degree l and order m in [-l, l]:
	//

	u32 l = input::argument_line<u32>(argc, argv, 'l', 1, 0, math::MAX_LEGENDRE_POLY_DEGREE, 0);

	s32 m_min = input::argument_line<s32>(argc, argv, 'm', 1, -as_s32(l), as_s32(l), -as_s32(l));

	s32 m_max = input::argument_line<s32>(argc, argv, 'm', 2, m_min, as_s32(l), as_s32(l));

	//
	// Theta Range:
	//

	u32 theta_count = input::argument_line<u32>(argc, argv, 't', 1, 1, u32_max, 180);

	f64 theta_min = input::argument_line<f64>(argc, argv, 't', 2, 0.0, 180.0, 0.0);

	f64 theta_max = input::argument_line<f64>(argc, argv, 't', 3, theta_min, 180.0, 180.0);

	f64 theta_step = (theta_max - theta_min)/as_f64(theta_count);

	//
	// Phi Range:
	//

	u32 phi_count = input::argument_line<u32>(argc, argv, 'p', 1, 1, u32_max, 360);

	f64 phi_min = input::argument_line<f64>(argc, argv, 'p', 2, 0.0, 360.0, 0.0);

	f64 phi_max = input::argument_line<f64>(argc, argv, 'p', 3, phi_min, 360.0, 360.0);

	f64 phi_step = (phi_max - phi_min)/as_f64(phi_count);

	//
	// Output:
	//

	print::timestamp();

	for (mut<s32> m = m_min; m <= m_max; ++m) {
		print::line("# l = ", l, ", m = ", m);

		for (mut<u32> th = 0; th < theta_count; ++th) {
			f64 theta = theta_min + as_f64(th)*theta_step;

			for (mut<u32> ph = 0; ph < phi_count; ++ph) {
				f64 phi = phi_min + as_f64(ph)*phi_step;

				c64 y = math::sphe_harmonics(l, m, theta, phi);

				print::line<24>(theta, phi, y.real(), y.imag());
			}

			if (phi_count > 1) {
				print::line();
			}
		}
	}

	return EXIT_SUCCESS;
}
