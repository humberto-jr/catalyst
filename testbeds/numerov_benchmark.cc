#include "modules/essentials.h"
#include "modules/numerov.h"
#include "modules/nist.h"
#include "modules/pes.h"

constexpr u8 PAD = 4;

void call_olson_smith_model(u32 l, f64 mass, f64 R, mat<f64> &v)
{
	v(0, 0) = pes::olson_smith_pra1971(0, 0, R) + numerov::centrifugal_term(l, mass, R);
	v(0, 1) = pes::olson_smith_pra1971(0, 1, R);
	v(1, 0) = pes::olson_smith_pra1971(1, 0, R);
	v(1, 1) = pes::olson_smith_pra1971(1, 1, R) + numerov::centrifugal_term(l, mass, R);
}

f64 propagate(u32 l)
{
	//
	// Collision energy and reduced mass:
	//

	constexpr f64 tot_energy = 70.9/nist::HARTREE_TO_EV;

	constexpr f64 mass = 6089.0;

	//
	// Scattering grid:
	//

	constexpr f64 R_inf = 50.0;

	constexpr f64 R_min = 0.1;

	constexpr f64 R_max = 6.0;

	constexpr f64 R_step = 0.001;

	constexpr u32 R_count = as_u32((R_max - R_min)/R_step);

	//
	// Asymptotic levels:
	//

	numerov::basis level(2);

	level[0].l = l;
	level[0].eigenval = pes::olson_smith_pra1971(0, 0, R_inf);

	level[1].l = l;
	level[1].eigenval = pes::olson_smith_pra1971(1, 1, R_inf);

	//
	// Propagation:
	//

	mat<f64> workspace(2, 2), old_ratio(2, 2), ratio(2, 2), pot_energy(2, 2);

	for (mut<u32> n = 0; n <= R_count; ++n) {
		f64 R = R_min + as_f64(n)*R_step;

		call_olson_smith_model(l, mass, R, pot_energy);

		ratio.swap(old_ratio);

		numerov::renormalized(mass, R_step, tot_energy, pot_energy, workspace, old_ratio, ratio);
	}

	//
	// S-Matrix:
	//

	mat<f64> k(2, 2), re_s(2, 2), im_s(2, 2);

	usize count = numerov::build_react_matrix(mass, R_step, R_max, tot_energy, ratio, level, k);

	assert(count == 2);

	numerov::build_scatt_matrix(k, re_s, im_s);

	//
	// Probability of transition 1->2:
	//

	c64 s = c64(re_s(0, 1), im_s(0, 1));

	return std::abs(s*s);
}

int main(int argc, char *argv[])
{
	print::line("# Test of Johnson's Numerov implementation");
	print::line("# Ref. problem: 1->2 transition probability during He^+ + Ne collisions at 70.9 eV [J. Com. Phys. 13, 445-449 (1973)]");
	print::line('#');
	print::line("#  l   Ref. (table 1)                 Numerov");
	print::line("# -------------------------------------------");

	print::line<PAD>(0,   ' ', as_f32(0.279E-3), ' ', propagate(0));
	print::line<PAD>(10,  ' ', as_f32(0.164E-2), ' ', propagate(10));
	print::line<PAD>(20,  ' ', as_f32(0.110E-1), ' ', propagate(20));
	print::line<PAD>(200, ' ', as_f32(0.215E-1), ' ', propagate(200));
	print::line<PAD>(202, ' ', as_f32(0.552E-1), ' ', propagate(202));
	print::line<PAD>(205, ' ', as_f32(0.900E-1), ' ', propagate(205));
	print::line<PAD>(209, ' ', as_f32(0.553E-1), ' ', propagate(209));
	print::line<PAD>(214, ' ', as_f32(0.487E-3), ' ', propagate(214));
	print::line<PAD>(290, ' ', as_f32(0.167E-4), ' ', propagate(290));
	print::line<PAD>(300, ' ', as_f32(0.146),    ' ', propagate(300));
	print::line<PAD>(310, ' ', as_f32(0.202),    ' ', propagate(310));
	print::line<PAD>(320, ' ', as_f32(0.941E-1), ' ', propagate(320));
	print::line<PAD>(330, ' ', as_f32(0.226E-1), ' ', propagate(330));
	print::line<PAD>(350, ' ', as_f32(0.329E-3), ' ', propagate(350));

	return EXIT_SUCCESS;
}
