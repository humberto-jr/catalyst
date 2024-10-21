#include "modules/essentials.h"
#include "modules/liblapack.h"
#include "user.h"

constexpr usize PLACEHOLDER = 0;

int main()
{
	//
	// Rotor quantum numbers:
	//

	const Range<u32> J_list = user::total_angular_momentum();

	const Range<u32> j_list = user::rotation_quantum_numbers();

	Range<u32> l_list = user::orbital_angular_momentum();

	s32 J_parity = user::parity();

	//
	// Vibrational grid:
	//

	const Range<u32> v_list = user::vibration_quantum_numbers();

	const Range<f64> r_list = user::vibration_grid();

	usize size = r_list.count();

	//
	// Arrangement (a = 1, b = 2, c = 3) and PES:
	//

	const char arrang = user::arrangement();

	pes::Frontend pes = user::extern_pes();

	f64 mass = (arrang == 'a'? pes.mass_bc() : (arrang == 'b'? pes.mass_ac() : pes.mass_ab()));

	//
	// Output:
	//

	file::Output basis = user::basis_output_file();

	basis.write(fgh::MAGIC_NUMBER);
	basis.write(fgh::FORMAT_VERSION);
	basis.write(PLACEHOLDER);
	basis.write(r_list);

	//
	// Summary:
	//

	print::timestamp();
	print::line("# Atom a: ", pes.atom_a());
	print::line("# Atom b: ", pes.atom_b());
	print::line("# Atom c: ", pes.atom_c());
	print::line("# Arrangement: ", arrang);
	print::line("# Output file: ", basis.filename.as_cstr());
	print::line("# PES shared library: ", pes.filename());
	print::line("# Diatomic reduc. mass: ", mass, " a.u.");
	print::line("#");
	print::line("#     Ch.      J       v       j       l       p         E (a.u.)                      E (cm-1)                      E (eV)");
	print::line("# ----------------------------------------------------------------------------------------------------------------------------------------");

	//
	// Resolve the diatomic eigenvalue problem for each j in a given arrangement:
	//

	mut<usize> count = 0;
	Vec<f64> eigenval(size);
	Vec<f64> eigenvec(size);
	Vec<f64> potential(size);
	Mat<f64> hamiltonian(size, size);

	for (u32 j : j_list.as_range_inclusive()) {
		for (auto r : r_list.indexed()) {
			switch (arrang) {
				case 'a': potential[r.index] = pes.diatom_bc(j, r.value); break;
				case 'b': potential[r.index] = pes.diatom_ac(j, r.value); break;
				case 'c': potential[r.index] = pes.diatom_ab(j, r.value); break;
			}
		}

		fgh::matrix(mass, r_list.step, potential, hamiltonian);

		lapack::syev(hamiltonian, eigenval);

		for (u32 v : v_list.as_range_inclusive()) {
			hamiltonian.col_copy(v, eigenvec);

			f64 norm = fgh::norm(r_list.step, eigenvec);

			for (u32 J : J_list.as_range_inclusive()) {
				l_list.min = std::abs(as_s32(J - j));
				l_list.max = J + j;

				for (u32 l : l_list.as_range_inclusive()) {
					s32 p = as_s32(std::pow(-1.0, j + l));

					if ((p == J_parity) || (J_parity == 0)) {
						basis.write(count);
						basis.write(j);
						basis.write(v);
						basis.write(J);
						basis.write(l);
						basis.write(p);
						basis.write(0u);
						basis.write(norm);
						basis.write(eigenval[v]);
						basis.write(eigenvec);

						print::line<8>(count, J, v, j, l, p,
						               ' ', eigenval[v],
						               ' ', eigenval[v]*nist::HARTREE_TO_WAVENUM,
						               ' ', eigenval[v]*nist::HARTREE_TO_EV);
						++count;
					}
				}
			}
		}
	}

	// NOTE: Rewriting the placeholder in the second entry with the total count.
	basis.seek_set(sizeof(fgh::MAGIC_NUMBER) + sizeof(fgh::FORMAT_VERSION));
	basis.write(count);

	return EXIT_SUCCESS;
}
