#include "modules/essentials.h"
#include "modules/liblapack.h"
#include "modules/input.h"
#include "modules/file.h"
#include "modules/pes.h"
#include "modules/fgh.h"

// Internals
#include "filename.h"
#include "key.h"

constexpr u32 PLACEHOLDER = 0;

int main()
{
	lapack::frontend lapack;

	//
	// Total angular momentum, J:
	//

	u32 J_min = input::keyword(key::J_min, 0u, u32_max, 0u);

	u32 J_max = input::keyword(key::J_max, J_min, u32_max, J_min);

	u32 J_step = input::keyword(key::J_step, 1u, u32_max, 1u);

	s32 J_parity = input::keyword(key::J_parity, -1, 1, 0);

	//
	// Vibrational quantum numbers, v:
	//

	u32 v_min = input::keyword(key::v_min, 0u, u32_max, 0u);

	u32 v_max = input::keyword(key::v_max, v_min, u32_max, v_min);

	u32 v_step = input::keyword(key::v_step, 1u, u32_max, 1u);

	//
	// Rotational quantum numbers, j:
	//

	u32 j_min = input::keyword(key::j_min, 0u, u32_max, 0u);

	u32 j_max = input::keyword(key::j_max, j_min, u32_max, j_min);

	u32 j_step = input::keyword(key::j_step, 1u, u32_max, 1u);

	//
	// Orbital angular momentum, l:
	//

	u32 l_step = input::keyword(key::l_step, 1u, u32_max, 1u);

	//
	// Vibrational grid:
	//

	u32 n_min = input::keyword(key::rovib_grid_start, 0u, u32_max, 0u);

	u32 r_count = input::keyword(key::rovib_grid_size, 1u, u32_max, 100u);

	f64 r_min = input::keyword(key::r_min, 0.0, f64_max, 0.5);

	f64 r_max = input::keyword(key::r_max, r_min, f64_max, r_min + 100.0);

	f64 r_step = (r_max - r_min)/as_f64(r_count);

	//
	// Isotopes and arrangement (a = 1, b = 2, c = 3):
	//

	const char arrang = as_char(96 + input::keyword(key::arrangement, 1, 3, 1));

	if ((arrang != 'a') && (arrang != 'b') && (arrang != 'c')) {
		print::error(WHERE, "Invalid arrangement ", arrang);
	}

	const auto atom_a = input::keyword(key::atom_a, nist::isotope::atom_unknown);
	const auto atom_b = input::keyword(key::atom_b, nist::isotope::atom_unknown);
	const auto atom_c = input::keyword(key::atom_c, nist::isotope::atom_unknown);

	//
	// PES:
	//

	const string pesname = input::keyword(key::extern_pes_filename);

	pes::frontend pes(pesname, atom_a, atom_b, atom_c);

	f64 mass = (arrang == 'a'? pes.mass_bc() : (arrang == 'b'? pes.mass_ac() : pes.mass_ab()));

	//
	// Output:
	//

	const string bufname = input::keyword(key::basis_output_filename, filename::fgh_basis);

	file::output basis(bufname.as_cstr());

	basis.write(fgh::MAGIC_NUMBER);
	basis.write(fgh::FORMAT_VERSION);
	basis.write(PLACEHOLDER);
	basis.write(n_min);
	basis.write(r_min);
	basis.write(r_max);
	basis.write(r_step);

	//
	// Summary:
	//

	print::timestamp();
	print::line("# Atom a: ", pes.atom_a());
	print::line("# Atom b: ", pes.atom_b());
	print::line("# Atom c: ", pes.atom_c());
	print::line("# Arrangement: ", arrang);
	print::line("# Output file: ", bufname.as_cstr());
	print::line("# PES shared library: ", pes.filename());
	print::line("# Diatomic reduc. mass: ", mass, " a.u.");
	print::line("#");
	print::line("#     Ch.      J       v       j       l       p         E (a.u.)                      E (cm-1)                      E (eV)");
	print::line("# ----------------------------------------------------------------------------------------------------------------------------------------");

	//
	// Resolve the diatomic eigenvalue problem for each j in a given arrangement:
	//

	mut<u32> count = 0;

	vec<f64> potential(r_count);
	potential = 0.0;

	vec<f64> eigenval(r_count);
	eigenval = 0.0;

	mat<f64> hamiltonian(r_count, r_count);
	hamiltonian = 0.0;

	for (mut<u32> j = j_min; j <= j_max; j += j_step) {

		for (mut<u32> n = 0; n < r_count; ++n) {
			f64 r = r_min + as_f64(n_min + n)*r_step;

			switch (arrang) {
				case 'a': potential[n] = pes.diatom_bc(j, r); break;
				case 'b': potential[n] = pes.diatom_ac(j, r); break;
				case 'c': potential[n] = pes.diatom_ab(j, r); break;
			}
		}

		fgh::matrix(mass, r_step, potential, hamiltonian);

		lapack.dsyev(hamiltonian, eigenval);

		for (mut<u32> v = v_min; v <= v_max; v += v_step) {
			auto eigenvec = (lapack::using_magma()? hamiltonian.row_view(v) : hamiltonian.col_view(v));

			f64 norm = fgh::norm(v, r_step, eigenvec);

			for (mut<u32> J = J_min; J <= J_max; J += J_step) {
				s32 l_min = as_s32(J - j);
				u32 l_max = J + j;

				for (mut<u32> l = std::abs(l_min); l <= l_max; l += l_step) {
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
