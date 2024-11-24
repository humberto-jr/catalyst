#include "modules/essentials.h"
#include "modules/numerov.h"

constexpr u8 PAD = 24;

int main(int argc, const char *argv[])
{
	if (argc == 1) {
		print::error("# Usage: ", argv[0], " <filename> [shift] [scale]");
	}

	numerov::ScattMatrix s(argv[1]);

	f64 shift = (argc > 2? as_f64(argv[2]) : 0.0);

	f64 scale = (argc > 3? as_f64(argv[3]) : 1.0);

	usize channel_count = s.channel_count();

	usize energy_count = s.energy_count();

	f64 mass = s.reduced_mass();

	//
	// Summary:
	//

	print::timestamp();
	print::line("# Channel count: ", channel_count);
	print::line("# Energy count: ", energy_count);
	print::line("# Energy shift: ", shift);
	print::line("# Energy scale: ", scale);
	print::line("# Reduced mass: ", mass, " a.u.");
	print::line("# S-matrix: ", s.filename());
	print::line("# Note: grep -A ", energy_count, " \"# (Ch. = $1,\" $filename | grep -A ", energy_count, " \"> (Ch. = $2,\"");
	print::line('#');

	//
	// Output:
	//

	for (mut<usize> channel_a = 0; channel_a < channel_count; ++channel_a) {
		for (mut<usize> channel_b = 0; channel_b < channel_count; ++channel_b) {
			bool was_closed = true;

			const auto &entry = s(channel_a, channel_b);

			f64 eigenval_in = (entry.eigenval_in + shift)*scale;

			f64 eigenval_out = (entry.eigenval_out + shift)*scale;

			for (mut<usize> n = 0; n < energy_count; ++n) {
				f64 total_energy = (entry.total_energy[n] + shift)*scale;

				if ((total_energy < eigenval_in) || (total_energy < eigenval_out)) {
					continue;
				}

				if (was_closed) {
					was_closed = false;

					print::line("# (",
					            "Ch. = ", channel_a,
					            ", v = ", entry.v_in,
					            ", j = ", entry.j_in,
					            ", l = ", entry.l_in,
					            ", n = ", entry.n_in,
					            ", J = ", entry.J_in,
					            ", eigenvalue = ", eigenval_in,
					            ") --> (",
					            "Ch. = ", channel_b,
					            ", v' = ", entry.v_out,
					            ", j' = ", entry.j_out,
					            ", l' = ", entry.l_out,
					            ", n' = ", entry.n_out,
					            ", J' = ", entry.J_out,
					            ", eigenvalue = ", eigenval_out, ')');

					print::line<PAD>("# Coll. energy", "Tot. energy", "k (a.u.)", "k' (a.u.)", "|S|^2", "re(S)", "im(S)");
				}

				c64 s = entry.value[n];

				c64 ss = std::conj(s)*s;

				f64 wavenum_in = numerov::wavenumber(mass, entry.total_energy[n], entry.eigenval_in);

				f64 wavenum_out = numerov::wavenumber(mass, entry.total_energy[n], entry.eigenval_out);

				print::line<PAD>(total_energy - eigenval_in, total_energy, wavenum_in, wavenum_out, ss.real(), s.real(), s.imag());
			}

			print::line();
		}
	}

	return EXIT_SUCCESS;
}
