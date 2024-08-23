#if !defined(FILENAME_HEADER)
	#define FILENAME_HEADER
	#include "modules/essentials.h"

	namespace filename {
		[[maybe_unused]]
		static constexpr c_str fgh_basis = "fgh_basis.bin\0";

		[[maybe_unused]]
		static constexpr c_str coupling_matrix = "coupling_matrix.bin\0";

		[[maybe_unused]]
		static constexpr c_str ratio_matrix = "ratio_matrix.bin\0";

		[[maybe_unused]]
		static constexpr c_str smatrix = "smatrix.bin\0";
	}
#endif
