#include "modules/essentials.h"
#include "modules/input.h"
#include "modules/math.h"

constexpr u8 PAD = 26;

int main(int argc, char *argv[])
{
	if (argc == 1) {
		print::error("# Usage: ", argv[0], " -l [min] [max] [step] -x [size] [min] [max]");
	}

	//
	// Degree l:
	//

	u32 l_min = input::argument_line(argc, argv, 'l', 1u, 0u, u32_max, 0u);

	u32 l_max = input::argument_line(argc, argv, 'l', 2u, l_min, u32_max, l_min);

	u32 l_step = input::argument_line(argc, argv, 'l', 3u, 1u, u32_max, 1u);

	//
	// Coordinate x:
	//

	u32 x_count = input::argument_line(argc, argv, 'x', 1u, 1u, u32_max, 1u);

	f64 x_min = input::argument_line(argc, argv, 'x', 2u, 0.0, f64_max, 0.0);

	f64 x_max = input::argument_line(argc, argv, 'x', 3u, x_min, f64_max, x_min);

	f64 x_step = (x_max - x_min)/as_f64(x_count);

	//
	// Output:
	//

	print::timestamp();
	print::line("# size = ", x_count);

	for (mut<u32> l = l_min; l <= l_max; l += l_step) {
		print::line("# l = ", l);
		print::line<PAD>("# x", "j (regular, 1st kind)", "y (irregular, 2nd kind)", "i (modified 1st kind)", "k (modified 2nd kind)");

		for (mut<u32> n = 0; n < x_count; ++n) {
			f64 x = x_min + as_f64(n)*x_step;

			f64 j = math::sphe_bessel('j', l, x);
			f64 y = math::sphe_bessel('y', l, x);
			f64 i = math::sphe_bessel('i', l, x);
			f64 k = math::sphe_bessel('k', l, x);

			print::line<PAD>(x, j, y, i, k);
		}

		print::line();
	}

	return EXIT_SUCCESS;
}
