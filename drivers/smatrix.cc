#include "modules/essentials.h"
#include "modules/numerov.h"
#include "modules/libtoml.h"

constexpr u8 PAD = 24;
constexpr u8 FORMAT_VERSION = 3;

struct Job {
	Mat<f64> k;
	Mat<f64> re_s;
	Mat<f64> im_s;
	mut<f64> total_energy;
};

int main(int argc, char *argv[])
{
	print::line("# ", argv[0]);
	print::timestamp();
	print::line();

	toml::Cin toml;

	//
	// S-matrix output:
	//

	file::Output smatrix = toml.output_filename("smatrix", "smatrix.bin");

	//
	// Numerov ratio matrices:
	//

	String filename = toml.string("numerov", "filename", "numerov_ratio_matrix.bin");

	numerov::Ratio solution(filename.as_cstr());

	const Range<f64> R_list = solution.grid_range();

	usize channel_count = solution.channel_count();

	f64 mass = solution.reduced_mass();

	//
	// Scattering basis set:
	//

	filename = toml.string("fgh", "filename", "atom+diatom_fgh_basis.bin");

	const numerov::Basis basis(filename);

	//
	// Collision energy:
	//

	usize energy_count = solution.energy_range().count();

	f64 shift = toml.value("energy", "shift", -f64_max, f64_max, 0.0);
	f64 scale = toml.value("energy", "scale", -f64_max, f64_max, 1.0);

	//
	// Summary:
	//

	print::line();
	print::line("# Channel count: ", channel_count);
	print::line("# Energy count: ", energy_count);
	print::line("# R value: ", R_list.max - R_list.step);
	print::line("# Reduced mass: ", mass, " a.u.");
	print::line("# NOTE: grep -A ", energy_count + 1, " \"# (Ch. = $1,\" $filename | grep -A ", energy_count + 1, " \"> (Ch. = $2,\"");
	print::line("#");

	//
	// Compute the augmented K-matrix and S-matrix for every energy.
	//

	Vec<Job> list(energy_count);

	for (mut<usize> task = 0; task < energy_count; ++task) {
		// NOTE: As of now, the Numerov driver only writes the energy-dependent
		// ratio matrices at the final R value.
		auto &ratio = solution(0, task);

		Mat<f64> k(channel_count, channel_count);

		usize open_count = numerov::build_react_matrix(mass,
		                                               R_list.step,
		                                               R_list.max,
		                                               ratio.energy,
		                                               ratio.value, basis, k);

		Mat<f64> re_s(open_count, open_count), im_s(open_count, open_count);

		if (open_count > 0) {
			k.resize(open_count, open_count);
			numerov::build_scatt_matrix(k, re_s, im_s);
		}

		list[task].k.swap(k);
		list[task].re_s.swap(re_s);
		list[task].im_s.swap(im_s);
		list[task].total_energy = ratio.energy;
	}

	//
	// Sort the result per a-->b transitions and print as a function of energy.
	//

	smatrix.write(numerov::MAGIC_NUMBER);
	smatrix.write(FORMAT_VERSION);
	smatrix.write(channel_count);
	smatrix.write(energy_count);
	smatrix.write(mass);

	for (mut<usize> channel_a = 0; channel_a < channel_count; ++channel_a) {
		for (mut<usize> channel_b = 0; channel_b < channel_count; ++channel_b) {
			bool was_closed = true;

			// NOTE: (x2 usize, 16 bytes) + (x14 s32, 56 bytes) + (x2 f64, 16 bytes).
			// It gives a total of 88 initial bytes for each pair of channels, ab.

			smatrix.write(channel_a);
			smatrix.write(channel_b);

			smatrix.write(basis.list[channel_a].n);
			smatrix.write(basis.list[channel_a].v);
			smatrix.write(basis.list[channel_a].j);
			smatrix.write(basis.list[channel_a].J);
			smatrix.write(basis.list[channel_a].l);
			smatrix.write(basis.list[channel_a].p);
			smatrix.write(basis.list[channel_a].c);
			smatrix.write(basis.list[channel_a].eigenval);

			smatrix.write(basis.list[channel_b].n);
			smatrix.write(basis.list[channel_b].v);
			smatrix.write(basis.list[channel_b].j);
			smatrix.write(basis.list[channel_b].J);
			smatrix.write(basis.list[channel_b].l);
			smatrix.write(basis.list[channel_b].p);
			smatrix.write(basis.list[channel_b].c);
			smatrix.write(basis.list[channel_b].eigenval);

			// NOTE: Shifted and/or scaled energies are for printing. Only the
			// original values in atomic units are written to binary files.
			f64 eigenval_a = (basis.list[channel_a].eigenval + shift)*scale;
			f64 eigenval_b = (basis.list[channel_b].eigenval + shift)*scale;

			for (mut<usize> task = 0; task < energy_count; ++task) {
				f64 total_energy = (list[task].total_energy + shift)*scale;

				// NOTE: (x1 usize, 8 bytes) + (x3 f64, 24 bytes).
				// For each chunk of 88 bytes, we add more energy_count*32 bytes.

				smatrix.write(task);
				smatrix.write(list[task].total_energy);

				if ((total_energy > eigenval_a) && (total_energy > eigenval_b)) {
					smatrix.write(list[task].re_s(channel_a, channel_b));
					smatrix.write(list[task].im_s(channel_a, channel_b));
				} else {
					smatrix.write(0.0);
					smatrix.write(0.0);
					continue;
				}

				if (was_closed) {
					was_closed = false;

					print::line("# (",
					            "Ch. = ", channel_a,
					            ", n = ", basis.list[channel_a].n,
					            ", v = ", basis.list[channel_a].v,
					            ", j = ", basis.list[channel_a].j,
					            ", l = ", basis.list[channel_a].l,
					            ", c = ", basis.list[channel_a].c,
					            ", J = ", basis.list[channel_a].J,
					            ", eigenvalue = ", eigenval_a,
					            ") --> (",
					            "Ch. = ", channel_b,
					            ", n' = ", basis.list[channel_b].n,
					            ", v' = ", basis.list[channel_b].v,
					            ", j' = ", basis.list[channel_b].j,
					            ", l' = ", basis.list[channel_b].l,
					            ", c' = ", basis.list[channel_b].c,
					            ", J' = ", basis.list[channel_b].J,
					            ", eigenvalue = ", eigenval_b, ')');

					print::line<PAD, '#'>("Coll. energy", "Tot. energy", "k (a.u.)", "k' (a.u.)", "|S|^2", "re(S)", "im(S)", "K (open-open block)");
				}

				f64 k = list[task].k(channel_a, channel_b);

				c64 s = c64(
					list[task].re_s(channel_a, channel_b),
					list[task].im_s(channel_a, channel_b)
				);

				c64 ss = std::conj(s)*s;

				f64 wavenum_a = numerov::wavenumber(mass,
				                                    list[task].total_energy,
				                                    basis.list[channel_a].eigenval);

				f64 wavenum_b = numerov::wavenumber(mass,
				                                    list[task].total_energy,
				                                    basis.list[channel_b].eigenval);

				print::line<PAD>(total_energy - eigenval_a, total_energy,
				                 wavenum_a, wavenum_b, ss.real(), s.real(), s.imag(), k);
			}

			print::line();
		}
	}

	return EXIT_SUCCESS;
}
