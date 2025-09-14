#include "modules/essentials.h"
#include "modules/liblapack.h"
#include "modules/libtoml.h"
#include "modules/fgh.h"

constexpr usize PLACEHOLDER = 0;

Range<s32> fine_struct_range(s32 n, u8 spin_mult)
{
	mut<s32> min = 0, max = 0, step = 0;

	// NOTE:
	// Since j = (N + elec. spin) is a half-integer in the doublet case, we
	// resolve them scaled by two to avoid using floating-point numbers. Thus,
	//
	//  j = N for singlet;
	// 2j = (2N - 1), (2N + 1) for doublet; and
	//  j = (N - 1), N, (N + 1) for triplet molecules.

	switch (spin_mult) {
		case 1:
		min = n;
		max = n;
		step = 1;
		break;

		case 2:
		min = (n > 0? 2*n - 1 : 1);
		max = 2*n + 1;
		step = 2;
		break;

		case 3:
		min = (n > 0? n - 1 : 1);
		max = n + 1;
		step = 1;
		break;

		default:
		print::error(WHERE, "Invalid spin multiplicity ", spin_mult);
	}

	return Range<s32>(min, max, step);
}

Range<s32> orbital_angular_momentum_range(s32 J, s32 j, u8 spin_mult)
{
	if (spin_mult != 2) {
		return Range<s32>(std::abs(J - j), (J + j), 1);
	} else {
		// NOTE: Since the total angular momentum is also a half-integer in the
		// doublet case, it is taken multiplied by two too. The orbital angular
		// momentum is an integer varying at steps of 1, thus, the list of l
		// values used below is bound between |2J - 2j|/2 and (2J + 2j)/2.
		return Range<s32>(std::abs(J - j)/2, (J + j)/2, 1);
	}
}

int main(int argc, char *argv[])
{
	print::line("# ", argv[0]);
	print::timestamp();
	print::line();

	toml::Cin toml;

	//
	// Fine structure:
	//

	f64 gamma = toml.value("diatom", "fine_struct", "spin_rotation_const", 0.0, f64_max, 0.0);

	f64 lambda = toml.value("diatom", "fine_struct", "spin_spin_const", 0.0, f64_max, 0.0);

	u8 spin_mult = ((gamma > 0.0) && (lambda > 0.0)? 3u : (gamma > 0.0? 2u : 1u));

	//
	// Rovibration diatomic basis:
	//

	Range<s32> n_list = toml.range("diatom", "rotation", 0, 0, 1);

	s32 nl_parity = toml.value("diatom", "rotation", "parity", -1, 1, 0);

	Range<s32> v_list = toml.range("diatom", "vibration", 0, 0, 1);

	Range<s32> J_list = toml.range("total_angular_momentum", 0, 0, (spin_mult == 2? 2 : 1));

	Range<f64> r_list = toml.range("jacobi", "r", 0.5, 30.0, 0.05);

	usize size = r_list.count();

	//
	// PES:
	//

	const char arrang = toml.pes_arrangement();

	pes::Frontend pes = toml.pes_extern_lib();

	f64 mass = (arrang == 'a'? pes.mass_bc() : (arrang == 'b'? pes.mass_ac() : pes.mass_ab()));

	//
	// FGH:
	//

	file::Output basis = toml.output_filename("fgh", "atom+diatom_fgh_basis.bin");

	basis.write(fgh::MAGIC_NUMBER);
	basis.write(fgh::FORMAT_VERSION);
	basis.write(PLACEHOLDER);
	basis.write(r_list);
	basis.write(spin_mult);

	//
	// Summary:
	//

	print::line();
	print::line("# Hund's case: (b)");
	print::line("# Elec. spin multiplicity: ", spin_mult);
	print::line("# Diatomic reduced mass: ", mass, " a.u.");
	print::line("#");

	if (spin_mult != 2) {
		print::line("#      Ch.      n       v       j       J       l       p         E (a.u.)                      E (cm-1)                      E (eV)");
	} else {
		print::line("#      Ch.      n       v      2j      2J       l       p         E (a.u.)                      E (cm-1)                      E (eV)");
	}

	print::line("# -------------------------------------------------------------------------------------------------------------------------------------------------");

	//
	// Resolve the diatomic eigenvalue problem for each N in a given arrangement:
	//

	mut<usize> count = 0;
	Vec<f64> eigenval(size);
	Vec<f64> eigenvec(size);
	Vec<f64> potential(size);
	Mat<f64> hamiltonian(size, size);

	for (s32 n : n_list.as_range_inclusive()) {
		for (auto r : r_list.indexed()) {
			switch (arrang) {
				case 'a': potential[r.index] = pes.diatom_bc(n, r.value); break;
				case 'b': potential[r.index] = pes.diatom_ac(n, r.value); break;
				case 'c': potential[r.index] = pes.diatom_ab(n, r.value); break;
			}
		}

		fgh::matrix(mass, r_list.step, potential, hamiltonian);

		lapack::syev(hamiltonian, eigenval);

		for (s32 v : v_list.as_range_inclusive()) {
			hamiltonian.col_copy(v, eigenvec);

			f64 norm = fgh::norm(r_list.step, eigenvec);

			mut<f64> splitting[3] = {0.0};

			mut<u8> sublevel = (n == 0? spin_mult - 1 : 0);

			if (spin_mult == 2) {
				splitting[0] = -0.5*gamma*as_f64(n + 1);
				splitting[1] =  0.5*gamma*as_f64(n);
			}

			if (spin_mult == 3) {
				f64 B = fgh::centrifugal_term(r_list, eigenvec);

				f64 a = as_f64(2*n - 1);
				f64 b = as_f64(2*n + 3);
				f64 c = 2.0*lambda*B;
				f64 d = gamma*as_f64(n);
				f64 e = gamma*as_f64(n + 1);

				f64 a_sq = a*a;
				f64 b_sq = b*b;
				f64 B_sq = B*B;
				f64 l_sq = lambda*lambda;

				splitting[0] = -B*a - lambda - std::sqrt(a_sq*B_sq + l_sq - c) - d;
				splitting[2] =  B*b - lambda - std::sqrt(b_sq*B_sq + l_sq - c) + e;
			}

			Range<s32> j_list = fine_struct_range(n, spin_mult);

			for (s32 j : j_list.as_range_inclusive()) {
				for (s32 J : J_list.as_range_inclusive()) {

					Range<s32> l_list = orbital_angular_momentum_range(J, j, spin_mult);

					for (s32 l : l_list.as_range_inclusive()) {
						s32 p = ((n + l)%2 == 0? 1 : -1);

						if ((p == nl_parity) || (nl_parity == 0)) {
							f64 energy = eigenval[v] + splitting[sublevel];

							basis.write(count);
							basis.write(n);
							basis.write(v);
							basis.write(j);
							basis.write(J);
							basis.write(l);
							basis.write(p);
							basis.write(0u);
							basis.write(norm);
							basis.write(energy);
							basis.write(eigenvec);

							print::line<8, '#'>(count, n, v, j, J, l, p,
								                ' ', energy,
								                ' ', energy*nist::HARTREE_TO_WAVENUM,
								                ' ', energy*nist::HARTREE_TO_EV);
							++count;
						}
					}
				}

				++sublevel;
			}

			assert(sublevel == spin_mult);
		}
	}

	// NOTE: Rewriting the placeholder in the second entry with the total count.
	basis.seek_set(sizeof(fgh::MAGIC_NUMBER) + sizeof(fgh::FORMAT_VERSION));
	basis.write(count);

	return EXIT_SUCCESS;
}
