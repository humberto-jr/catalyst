#if !defined(USER_HEADER)
	#define USER_HEADER
	#include "modules/essentials.h"
	#include "modules/input.h"
	#include "modules/file.h"
	#include "modules/pes.h"

	// Internals
	#include "filename.h"
	#include "key.h"

	namespace user {
		[[maybe_unused]]
		static Range<u32> total_angular_momentum()
		{
			u32 min = input::keyword(key::J_min, 0u, u32_max, 0u);
			u32 max = input::keyword(key::J_max, min, u32_max, min);
			u32 step = input::keyword(key::J_step, 1u, u32_max, 1u);

			return Range<u32>(min, max, step);
		}

		[[maybe_unused]]
		static inline s32 parity()
		{
			return input::keyword(key::J_parity, -1, 1, 0);
		}

		[[maybe_unused]]
		static Range<u32> vibration_quantum_numbers()
		{
			u32 min = input::keyword(key::v_min, 0u, u32_max, 0u);
			u32 max = input::keyword(key::v_max, min, u32_max, min);
			u32 step = input::keyword(key::v_step, 1u, u32_max, 1u);

			return Range<u32>(min, max, step);
		}

		[[maybe_unused]]
		static Range<u32> rotation_quantum_numbers()
		{
			u32 min = input::keyword(key::j_min, 0u, u32_max, 0u);
			u32 max = input::keyword(key::j_max, min, u32_max, min);
			u32 step = input::keyword(key::j_step, 1u, u32_max, 1u);

			return Range<u32>(min, max, step);
		}

		[[maybe_unused]]
		static Range<u32> orbital_angular_momentum()
		{
			u32 min = input::keyword(key::l_min, 0u, u32_max, 0u);
			u32 max = input::keyword(key::l_max, min, u32_max, min);
			u32 step = input::keyword(key::l_step, 1u, u32_max, 1u);

			return Range<u32>(min, max, step);
		}

		[[maybe_unused]]
		static Range<u32> multipole_terms(u32 default_chunk = 20u)
		{
			u32 min = input::keyword(key::lambda_min, 0u, u32_max, 0u);
			u32 max = input::keyword(key::lambda_max, min, u32_max, min + default_chunk);

			// NOTE: The Legendre multipoles are indexed at steps of 1 or 2,
			// where 2 is typically used for homonuclear systems.
			u32 step = input::keyword(key::lambda_step, 1u, 2u, 1u);

			return Range<u32>(min, max, step);
		}

		[[maybe_unused]]
		static Range<f64> vibration_grid()
		{
			f64 min = input::keyword(key::r_min, 0.0, f64_max, 0.5);
			f64 max = input::keyword(key::r_max, min, f64_max, min + 100.0);
			u32 count = input::keyword(key::rovib_grid_size, 1u, u32_max, 100u);

			return Range<f64>(min, max, (max - min)/as_f64(count));
		}

		[[maybe_unused]]
		static Range<f64> scattering_grid()
		{
			f64 min = input::keyword(key::R_min, 0.0, f64_max, 0.5);
			f64 max = input::keyword(key::R_max, min, f64_max, min + 100.0);
			u32 count = input::keyword(key::scatt_grid_size, 1u, u32_max, 100u);

			return Range<f64>(min, max, (max - min)/as_f64(count));
		}

		[[maybe_unused]]
		static Range<f64> polar_angle_grid()
		{
			f64 min = input::keyword(key::theta_min, 0.0, 180.0, 0.0);
			f64 max = input::keyword(key::theta_max, min, 180.0, 180.0);
			u32 count = input::keyword(key::theta_grid_size, 1u, u32_max, 180u);

			return Range<f64>(min, max, (max - min)/as_f64(count));
		}

		[[maybe_unused]]
		static char arrangement()
		{
			// NOTE: The ASCII codes for the characters 'a', 'b', and 'c' are
			// 97, 98 and 99, respectively.
			const char arrang = as_char(96 + input::keyword(key::arrangement, 1, 3, 1));

			if ((arrang != 'a') && (arrang != 'b') && (arrang != 'c')) {
				print::error(WHERE, "Invalid arrangement ", arrang);
			}

			return arrang;
		}

		[[maybe_unused]]
		static pes::Frontend extern_pes()
		{
			auto filename = input::keyword(key::extern_pes_filename);
			auto atom_a = input::keyword(key::atom_a, nist::Isotope::atom_unknown);
			auto atom_b = input::keyword(key::atom_b, nist::Isotope::atom_unknown);
			auto atom_c = input::keyword(key::atom_c, nist::Isotope::atom_unknown);

			return pes::Frontend(filename, atom_a, atom_b, atom_c);
		}

		[[maybe_unused]]
		static inline file::Output basis_output_file()
		{
			auto filename = input::keyword(key::basis_output_filename, filename::fgh_basis);
			return file::Output(filename);
		}

		[[maybe_unused]]
		static inline f64 energy_shift()
		{
			return input::keyword(key::energy_shift, -f64_max, f64_max, 0.0);
		}

		[[maybe_unused]]
		static inline f64 energy_scale()
		{
			return input::keyword(key::energy_scale, -f64_max, f64_max, 1.0);
		}
	}
#endif
