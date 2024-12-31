#include "modules/essentials.h"
#include "modules/numerov.h"
#include "modules/input.h"

constexpr u8 PAD = 24;
constexpr f64 THETA_MIN = 0.0;
constexpr f64 THETA_MAX = 180.0;

struct Job {
	mut<u32> v_in;
	mut<u32> j_in;
	mut<u32> n_in;
	mut<u32> J_in;

	mut<u32> v_out;
	mut<u32> j_out;
	mut<u32> n_out;
	mut<u32> J_out;

	Range<f64> theta_list;

	mut<f64> energy_shift;
	mut<f64> energy_scale;
	mut<f64> sigma_scale;
};

Job read_arguments(s32 argc, char* argv[])
{
	Job params;

	//
	// Entrance channel:
	//

	params.v_in = input::argument_line(argc, argv, 'i', 1u, 0u, u32_max, 0u);

	params.j_in = input::argument_line(argc, argv, 'i', 2u, 0u, u32_max, 0u);

	params.n_in = input::argument_line(argc, argv, 'i', 3u, 0u, u32_max, 0u);

	params.J_in = 0;

	//
	// Exit channel:
	//

	params.v_out = input::argument_line(argc, argv, 'f', 1u, 0u, u32_max, 0u);

	params.j_out = input::argument_line(argc, argv, 'f', 2u, 0u, u32_max, 0u);

	params.n_out = input::argument_line(argc, argv, 'f', 3u, 0u, u32_max, 0u);

	params.J_out = 0;

	//
	// Scattering polar angle, theta:
	//

	u32 theta_count = input::argument_line(argc, argv, 't', 1u, 9u, u32_max, 180u);

	f64 theta_step = (THETA_MAX - THETA_MIN)/as_f64(theta_count);

	params.theta_list = Range<f64>(THETA_MIN, THETA_MAX, theta_step);

	//
	// Energy/cross-section scale and shift:
	//

	params.energy_shift = input::argument_line(argc, argv, 's', 1u, -f64_max, f64_max, 0.0);

	params.energy_scale = input::argument_line(argc, argv, 's', 2u, -f64_max, f64_max, 1.0);

	params.sigma_scale = input::argument_line(argc, argv, 's', 3u, -f64_max, f64_max, 1.0);

	return params;
}

void print_channel_header(const Job &params,
                          const Range<usize> &channel_in,
                          const Range<usize> &channel_out,
                          f64 eigenval_in, f64 eigenval_out,
                          s32 m_in = s32_max, s32 m_out = s32_max)
{
	if ((m_in != s32_max) && (m_out != s32_max)) {
		print::line("# (Ch. = ", channel_in.min, '-', channel_in.max,
			        ", v = ", params.v_in,
			        ", j = ", params.j_in,
			        ", m = ", m_in,
		            ", n = ", params.n_in,
			        ", J = ", params.J_in,
			        ", eigenvalue = ", eigenval_in,
			        ") --> (",
			        "Ch. = ", channel_out.min, '-', channel_out.max,
			        ", v' = ", params.v_out,
			        ", j' = ", params.j_out,
			        ", m' = ", m_out,
		            ", n' = ", params.n_out,
			        ", J' = ", params.J_out,
			        ", eigenvalue = ", eigenval_out, ')');
	} else {
		print::line("# (Ch. = ", channel_in.min, '-', channel_in.max,
			        ", v = ", params.v_in,
			        ", j = ", params.j_in,
		            ", n = ", params.n_in,
			        ", J = ", params.J_in,
			        ", eigenvalue = ", eigenval_in,
			        ") --> (",
			        "Ch. = ", channel_out.min, '-', channel_out.max,
			        ", v' = ", params.v_out,
			        ", j' = ", params.j_out,
		            ", n' = ", params.n_out,
			        ", J' = ", params.J_out,
			        ", eigenvalue = ", eigenval_out, ')');
	}
}

bool print_cross_section(const Job &params, numerov::ScattMatrix &s)
{
	//
	// S-matrix input:
	//

	Vec<f64> energy_list(s.energy_count());

	const Range<usize> channel_list(0, s.channel_count());

	//
	// Entrance channel:
	//

	mut<f64> eigenval_in = 0.0;

	Vec<f64> wavenum_in(s.energy_count());

	Range<usize> entrance_channel(usize_max, usize_max);

	//
	// Exit channel:
	//

	mut<f64> eigenval_out = 0.0;

	Vec<f64> wavenum_out(s.energy_count());

	Range<usize> exit_channel(usize_max, usize_max);

	//
	// Step 1: Find the range of channel indices containing the lowest and highest
	// values of the orbital angular momentum l for both entrance and exit channels.
	//

	for (usize channel_index : channel_list) {
		const auto &entry = s(channel_index, channel_index);

		if ((params.J_in < entry.J_in) || (params.J_out < entry.J_out)) {
			// NOTE: In this case, the actual J (J') value was not found, but may
			// still be stored in the file. Thus, let's just pretend it is all
			// done, return and go to the next J.
			return true;
		}

		if ((entry.v_in == params.v_in) && (entry.j_in == params.j_in) && (entry.n_in == params.n_in) && (entry.J_in == params.J_in)) {
			if (channel_index < entrance_channel.min) {
				entrance_channel.min = channel_index;
				eigenval_in = entry.eigenval_in;
			}

			entrance_channel.max = channel_index;
		}

		if ((entry.v_out == params.v_out) && (entry.j_out == params.j_out) && (entry.n_out == params.n_out) && (entry.J_out == params.J_out)) {
			if (channel_index < exit_channel.min) {
				exit_channel.min = channel_index;
				eigenval_out = entry.eigenval_out;
			}

			exit_channel.max = channel_index;
		}

		if ((entry.v_in > params.v_in) && (entry.j_in > params.j_in) && (entry.n_in >= params.n_in) && (entry.J_in >= params.J_in) && (entry.v_out > params.v_out) && (entry.j_out > params.j_out) && (entry.n_out >= params.n_out) && (entry.J_out >= params.J_out)) {
			// NOTE: We now leave the loop early and take this opportunity to backup
			// the total energy and to compute the incoming and outgoing wavenumbers
			// from the last S-matrix entry. Assuming all entries are defined for
			// the same values of energy.

			for (auto energy : energy_list) {
				energy.value = entry.total_energy[energy.index];
				wavenum_in[energy.index] = numerov::wavenumber(s.reduced_mass(), entry.total_energy[energy.index], eigenval_in);
				wavenum_out[energy.index] = numerov::wavenumber(s.reduced_mass(), entry.total_energy[energy.index], eigenval_out);
			}

			break;
		}
	}

	if ((entrance_channel.min == usize_max) || (entrance_channel.max == usize_max)) {
		return false;
	}

	if ((exit_channel.min == usize_max) || (exit_channel.max == usize_max)) {
		return false;
	}

	//
	// Summary:
	//

	print::line("# Num. of channels: ", channel_list.max);
	print::line("# Num. of energies: ", s.energy_count());
	print::line("# Energy shift: ", params.energy_shift);
	print::line("# Energy scale: ", params.energy_scale);
	print::line("# Sigma scale: ", params.sigma_scale);
	print::line("# Reduced mass: ", s.reduced_mass(), " a.u.");
	print::line("# S-matrix: ", s.filename());
	print::line('#');

	//
	// Step 2: For a given (v, j, n) and (v', j', n'), build the m- and m'-dependent
	// scattering amplitudes f for every theta and energy value, summed over l and l'.
	// For details, see Eq. (19)-(21) of R. T. Pack. J. Chem. Phys. 60, 633-639 (1974).
	//

	numerov::ScattAmplitude f_list(params.j_in,
	                               params.j_out,
	                               params.theta_list.count() + 1, s.energy_count());

	const Range<usize> mm_list(0, f_list.mm_count());

	for (usize mm_index : mm_list) {
		s32 m_in = f_list(mm_index).m_in;

		s32 m_out = f_list(mm_index).m_out;

		for (auto theta : params.theta_list.as_range_inclusive().indexed()) {
			Vec<c64> &f_mm = f_list(mm_index, theta.index);

			for (usize channel_in : entrance_channel.as_range_inclusive()) {
				for (usize channel_out : exit_channel.as_range_inclusive()) {
					const auto &entry = s(channel_in, channel_out);

					assert(params.v_in == entry.v_in);
					assert(params.j_in == entry.j_in);
					assert(params.J_in == entry.J_in);
					assert(params.n_in == entry.n_in);
					assert(eigenval_in == entry.eigenval_in);

					assert(params.v_out == entry.v_out);
					assert(params.j_out == entry.j_out);
					assert(params.J_out == entry.J_out);
					assert(params.n_out == entry.n_out);
					assert(eigenval_out == entry.eigenval_out);

					// NOTE: Here, f is accumulating l- and l'-dependent results for fixed m and m'.
					numerov::build_scatt_amplitude(entry, m_in, m_out, theta.value, 0.0, f_mm);
				}
			}
		}
	}

	// NOTE: Both quantities are only used for printing from this point on.
	eigenval_in = (eigenval_in + params.energy_shift)*params.energy_scale;
	eigenval_out = (eigenval_out + params.energy_shift)*params.energy_scale;

	//
	// Step 3: Now, use the scattering amplitudes to build both differential and
	// integral cross-sections, sigma. See Eq. (21)-(22) of R. T. Pack. J. Chem.
	// Phys. 60, 633-639 (1974).
	//

	Vec<f64> int_sigma(s.energy_count());

	Mat<c64> f_sum(params.theta_list.count() + 1lu, s.energy_count());

	Mat<f64> dif_sigma(params.theta_list.count() + 1lu, s.energy_count());

	numerov::build_cross_section(f_list, params.j_in,
	                             wavenum_in, wavenum_out, f_sum, dif_sigma, int_sigma);

	//
	// Step 4: Print the state-to-state integral cross-section:
	//

	print_channel_header(params, entrance_channel, exit_channel, eigenval_in, eigenval_out);

	print::line<PAD>("# Coll. energy", "Tot. energy", "Int. cross-section");

	for (auto energy : energy_list) {
		// NOTE: The total energy is only used for printing from now on.
		energy.value = (energy.value + params.energy_shift)*params.energy_scale;

		f64 sigma = int_sigma[energy.index]*params.sigma_scale;

		print::line<PAD>(energy.value - eigenval_in, energy.value, sigma);
	}

	print::line();

	//
	// Step 5: Print the state-to-state differential cross-section, summed over
	// l, l', m, m', and averaged over the initial 2j + 1 projections of j.
	//

	print_channel_header(params, entrance_channel, exit_channel, eigenval_in, eigenval_out);

	print::line<PAD>("# theta", "Coll. energy", "Tot. energy", "Dif. cross-section", "|f|^2", "re(f)", "im(f)");

	for (auto theta : params.theta_list.as_range_inclusive().indexed()) {
		for (auto energy : energy_list) {
			c64 f = f_sum(theta.index, energy.index);

			c64 fxf_abs = std::conj(f)*f;

			assert(fxf_abs.imag() == 0.0);

			f64 sigma = dif_sigma(theta.index, energy.index)*params.sigma_scale;

			print::line<PAD>(theta.value,
			                 energy.value - eigenval_in,
			                 energy.value, sigma, fxf_abs.real(), f.real(), f.imag());
		}

		print::line();
	}

	//
	// Step 4: Print the partial non-averaged m- and m'-dependent differential
	// cross-section summed over l and l' values.
	//

	for (usize mm_index : mm_list) {
		print_channel_header(params, entrance_channel, exit_channel,
		                     eigenval_in, eigenval_out, f_list(mm_index).m_in, f_list(mm_index).m_out);

		print::line<PAD>("# theta", "Coll. energy", "Tot. energy", "Dif. cross-section", "|f|^2", "re(f)", "im(f)");;

		for (auto theta : params.theta_list.as_range_inclusive().indexed()) {
			for (auto energy : energy_list) {
				// NOTE: m-dependent results are not averaged over the initial
				// 2j + 1 projections of j.
				f64 fact = wavenum_out[energy.index]/wavenum_in[energy.index];

				c64 f_mm = f_list(mm_index, theta.index, energy.index);

				c64 fxf_abs = std::conj(f_mm)*f_mm;

				assert(fxf_abs.imag() == 0.0);

				f64 sigma = fact*fxf_abs.real()*params.sigma_scale;

				print::line<PAD>(theta.value,
				                 energy.value - eigenval_in,
				                 energy.value, sigma, fxf_abs.real(), f_mm.real(), f_mm.imag());
			}

			print::line();
		}
	}

	return true;
}

int main(int argc, char *argv[])
{
	if (argc == 1) {
		print::error("# Usage: ", argv[0], " [filename] -i [v] [j] [n] -f [v'] [j'] [n'] -t [size] -s [energy shift] [energy scale] [cross sec. scale]");
	}

	auto params = read_arguments(argc, argv);

	print::timestamp();

	for (mut<s32> n = 1; n < argc; ++n) {
		if (argv[n][0] == '-') {
			break;
		}

		bool is_found = true;

		numerov::ScattMatrix s(argv[n]);

		params.J_in = params.J_out = 0;

		while (is_found) {
			is_found = print_cross_section(params, s);

			params.J_in += 1;
			params.J_out = params.J_in;
		}
	}

	return EXIT_SUCCESS;
}
