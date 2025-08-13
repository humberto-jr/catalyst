#include "modules/essentials.h"
#include "modules/liblapack.h"
#include "modules/libtoml.h"
#include "modules/fgh.h"

constexpr usize PLACEHOLDER = 0;

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

	u8 spin_mult = ((gamma > 0.0) && (lambda > 0.0)? 3 : (gamma > 0.0? 2 : 1));

	//
	// Total angular momentum:
	//

	Range<u32> J_list = toml.range("total_angular_momentum", 0u, u32_max);

	s32 J_parity = toml.value("total_angular_momentum", "parity", -1, 1, 0);

	//
	// Rovibration diatomic basis:
	//

	Range<u32> j_list = toml.range("diatom", "rotation", (spin_mult == 1? 0 : 1), u32_max);

	Range<u32> v_list = toml.range("diatom", "vibration", 0u, u32_max);

	//
	// PES:
	//

	const char arrang = toml.pes_arrangement();

	pes::Frontend pes = toml.pes_extern_lib();

	f64 mass = (arrang == 'a'? pes.mass_bc() : (arrang == 'b'? pes.mass_ac() : pes.mass_ab()));

	//
	// FGH:
	//

	Range<f64> r_list = toml.range("fgh", 0.0, f64_max, 0.25);

	file::Output basis = toml.output_filename("fgh", "fgh_basis.bin");

	usize size = r_list.count();

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
	print::line("# Diatomic reduc. mass: ", mass, " a.u.");
	print::line("#");
	print::line("#      Ch.      J       v       j       l       p         E (a.u.)                      E (cm-1)                      E (eV)");
	print::line("# -----------------------------------------------------------------------------------------------------------------------------------------");

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
				Range<u32> l_list(std::abs(as_s32(J - j)), J + j, 1);

				for (u32 l : l_list.as_range_inclusive()) {
					s32 p = ((j + l)%2 == 0? 1 : -1);

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

						print::line<8, '#'>(count, J, v, j, l, p,
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
