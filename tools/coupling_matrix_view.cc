#include "modules/essentials.h"
#include "modules/liblapack.h"
#include "modules/numerov.h"
#include "modules/input.h"

constexpr u8 PAD = 24;
constexpr f64 EPS = 1.0E-12;

int main(int argc, char *argv[])
{
	if (argc < 2) {
		print::error("# Usage: ", argv[0], " [filename] -s [energy shift] [energy scale]");
	}

	numerov::Potential coupling(argv[1]);

	f64 mass = coupling.reduced_mass();

	Range<f64> R_list = coupling.grid_range();

	usize channel_count = coupling.channel_count();

	f64 shift = input::argument_line(argc, argv, 's', 1u, -f64_max, f64_max, 0.0);
	f64 scale = input::argument_line(argc, argv, 's', 2u, -f64_max, f64_max, 1.0);

	//
	// Summary:
	//

	print::timestamp();
	print::line("# Grid size: ", R_list.count());
	print::line("# Num. of channels: ", channel_count);
	print::line("# Coupling potential: ", coupling.filename());
	print::line("# Reduced mass: ", mass, " a.u.");
	print::line("#");

	//
	// Diagonalize the R-dependent potentials:
	//

	Vec<Vec<f64>> result(R_list.count());

	for (auto R : R_list.indexed()) {
		auto &entry = coupling[R.index];

		assert(std::abs(R.value - entry.R) < EPS);

		Vec<f64> eigenval(channel_count);

		lapack::syev(entry.value, eigenval);

		result[R.index].swap(eigenval);
	}

	//
	// Output:
	//

	for (mut<usize> channel = 0; channel < channel_count; ++channel) {
		print::line("# Channel = ", channel);
		print::line<PAD>("# R (a.u.)", "Energy");

		for (auto R : R_list.indexed()) {
			// NOTE: Due to the data layout and for the sake of the most readable
			// output format, this loop is fairly inefficient by accessing rows
			// at fixed columns.
			print::line<PAD>(R.value, (result[R.index][channel] + shift)*scale);
		}

		print::line();
	}

	return EXIT_SUCCESS;
}
