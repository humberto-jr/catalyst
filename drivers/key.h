#if !defined(KEY_HEADER)
	#define KEY_HEADER
	#include "modules/essentials.h"

	namespace key {
		// NOTE: Below, a list of keys is provided so that all drivers should refer
		// to the same input keywords whenever referring to the same quantities. It
		// also makes it simple to modify keywords consistently among all programs.
		// The input keyword constants defined here are not following the convention
		// of all-in-uppercase on purpose.

		[[maybe_unused]]
		static constexpr c_str use_omp = "use_omp\0";

		[[maybe_unused]]
		static constexpr c_str J_min = "J_min\0";

		[[maybe_unused]]
		static constexpr c_str J_max = "J_max\0";

		[[maybe_unused]]
		static constexpr c_str J_step = "J_step\0";

		[[maybe_unused]]
		static constexpr c_str J_parity = "J_parity\0";

		[[maybe_unused]]
		static constexpr c_str j_min = "j_min\0";

		[[maybe_unused]]
		static constexpr c_str j_max = "j_max\0";

		[[maybe_unused]]
		static constexpr c_str j_step = "j_step\0";

		[[maybe_unused]]
		static constexpr c_str l_min = "l_min\0";

		[[maybe_unused]]
		static constexpr c_str l_max = "l_max\0";

		[[maybe_unused]]
		static constexpr c_str l_step = "l_step\0";

		[[maybe_unused]]
		static constexpr c_str v_min = "v_min\0";

		[[maybe_unused]]
		static constexpr c_str v_max = "v_max\0";

		[[maybe_unused]]
		static constexpr c_str v_step = "v_step\0";

		[[maybe_unused]]
		static constexpr c_str r_min = "r_min\0";

		[[maybe_unused]]
		static constexpr c_str r_max = "r_max\0";

		[[maybe_unused]]
		static constexpr c_str r_step = "r_step\0";

		[[maybe_unused]]
		static constexpr c_str R_min = "R_min\0";

		[[maybe_unused]]
		static constexpr c_str R_max = "R_max\0";

		[[maybe_unused]]
		static constexpr c_str R_step = "R_step\0";

		[[maybe_unused]]
		static constexpr c_str E_min = "E_min\0";

		[[maybe_unused]]
		static constexpr c_str E_max = "E_max\0";

		[[maybe_unused]]
		static constexpr c_str E_step = "E_step\0";

		[[maybe_unused]]
		static constexpr c_str atom_a = "atom_a\0";

		[[maybe_unused]]
		static constexpr c_str atom_b = "atom_b\0";

		[[maybe_unused]]
		static constexpr c_str atom_c = "atom_c\0";

		[[maybe_unused]]
		static constexpr c_str atom_d = "atom_d\0";

		[[maybe_unused]]
		static constexpr c_str arrangement = "arrang\0";

		[[maybe_unused]]
		static constexpr c_str theta_min = "theta_min\0";

		[[maybe_unused]]
		static constexpr c_str theta_max = "theta_max\0";

		[[maybe_unused]]
		static constexpr c_str theta_step = "theta_step\0";

		[[maybe_unused]]
		static constexpr c_str lambda_min = "lambda_min\0";

		[[maybe_unused]]
		static constexpr c_str lambda_max = "lambda_max\0";

		[[maybe_unused]]
		static constexpr c_str lambda_step = "lambda_step\0";

		[[maybe_unused]]
		static constexpr c_str energy_shift = "energy_shift\0";

		[[maybe_unused]]
		static constexpr c_str energy_scale = "energy_scale\0";

		[[maybe_unused]]
		static constexpr c_str rovib_grid_start = "rovib_grid_start\0";

		[[maybe_unused]]
		static constexpr c_str rovib_grid_size = "rovib_grid_size\0";

		[[maybe_unused]]
		static constexpr c_str scatt_grid_start = "scatt_grid_start\0";

		[[maybe_unused]]
		static constexpr c_str scatt_grid_size = "scatt_grid_size\0";

		[[maybe_unused]]
		static constexpr c_str theta_grid_start = "theta_grid_start\0";

		[[maybe_unused]]
		static constexpr c_str theta_grid_size = "theta_grid_size\0";

		[[maybe_unused]]
		static constexpr c_str coll_grid_size = "coll_grid_size\0";

		[[maybe_unused]]
		static constexpr c_str extern_pes_filename = "pes_extern_lib\0";

		[[maybe_unused]]
		static constexpr c_str basis_output_filename = "basis_set_output\0";

		[[maybe_unused]]
		static constexpr c_str basis_input_filename = "basis_set_input\0";

		[[maybe_unused]]
		static constexpr c_str coupling_output_filename = "coupling_matrix_output\0";

		[[maybe_unused]]
		static constexpr c_str coupling_input_filename = "coupling_matrix_input\0";

		[[maybe_unused]]
		static constexpr c_str logd_output_filename = "logd_matrix_output\0";

		[[maybe_unused]]
		static constexpr c_str numerov_output_filename = "numerov_ratio_output\0";

		[[maybe_unused]]
		static constexpr c_str smatrix_input_filename = "numerov_ratio_input\0";

		[[maybe_unused]]
		static constexpr c_str smatrix_output_filename = "smatrix_output\0";
	}
#endif
