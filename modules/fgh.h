#if !defined(FGH_HEADER)
	#define FGH_HEADER
	#include "essentials.h"
	#include "file.h"

	namespace fgh {
		static constexpr u32 MAGIC_NUMBER = 464748u;

		void matrix(f64 mass, f64 step, const vec64 &potential, mat64 &result);

		void matrix(f64 mass, f64 step, const vec<mat64> &potential, mat64 &result);
	}
#endif
