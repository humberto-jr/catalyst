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

	u32 channel_count = s.channel_count();

	u32 energy_count = s.energy_count();

	//
	// Summary:
	//

	print::timestamp();
	print::line("# Num. of channels: ", channel_count);
	print::line("# Num. of energies: ", energy_count);
	print::line("# Energy shift: ", shift);
	print::line("# Energy scale: ", scale);
	print::line("# Reduced mass: ", s.reduced_mass(), " a.u.");
	print::line("# Input file: ", s.filename());
	print::line("# Note: grep -A ", energy_count + 1, " \"# (Ch. = $1,\" $filename | grep -A ", energy_count + 1, " \"> (Ch. = $2,\"");
	print::line('#');

	//
	// Output:
	//

	for (mut<u32> channel_a = 0; channel_a < channel_count; ++channel_a) {
		for (mut<u32> channel_b = 0; channel_b < channel_count; ++channel_b) {
			bool was_closed = true;

			const auto entry = s(channel_a, channel_b);

			f64 eigenval_in = (entry->eigenval_in + shift)*scale;

			f64 eigenval_out = (entry->eigenval_out + shift)*scale;

			for (mut<u32> n = 0; n < energy_count; ++n) {
				f64 total_energy = (entry->total_energy[n] + shift)*scale;

				if ((total_energy < eigenval_in) || (total_energy < eigenval_out)) {
					continue;
				}

				if (was_closed) {
					print::line("# (",
					            "Ch. = ", channel_a,
					            ", v = ", entry->v_in,
					            ", j = ", entry->j_in,
					            ", l = ", entry->l_in,
					            ", J = ", entry->J_in,
					            ", eigenvalue = ", eigenval_in,
					            ") --> (",
					            "Ch. = ", channel_b,
					            ", v' = ", entry->v_out,
					            ", j' = ", entry->j_out,
					            ", l' = ", entry->l_out,
					            ", J' = ", entry->J_out,
					            ", eigenvalue = ", eigenval_out, ')');

					print::line<PAD>("# Coll. energy", "Tot. energy", "k (a.u.)", "k' (a.u.)", "|S|^2", "re(S)", "im(S)");
					was_closed = false;
				}

				f64 re_s = entry->value[n].real();

				f64 im_s = entry->value[n].imag();

				f64 ss = std::abs(entry->value[n]*entry->value[n]);

				f64 wavenum_in = std::sqrt(2.0*entry->mass*(entry->total_energy[n] - entry->eigenval_in));

				f64 wavenum_out = std::sqrt(2.0*entry->mass*(entry->total_energy[n] - entry->eigenval_out));

				print::line<PAD>(total_energy - eigenval_in, total_energy, wavenum_in, wavenum_out, ss, re_s, im_s);
			}

			print::line();
		}
	}

	return EXIT_SUCCESS;
}
