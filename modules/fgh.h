#if !defined(FGH_HEADER)
	#define FGH_HEADER
	#include "essentials.h"
	#include "file.h"

	namespace fgh {
		static constexpr u8 FORMAT_VERSION = 1;

		static constexpr u32 MAGIC_NUMBER = 464748u;

		static constexpr usize BASIS_FILE_HEADER = sizeof(MAGIC_NUMBER) + sizeof(FORMAT_VERSION) + 2*sizeof(u32) + 3*sizeof(f64);

		void matrix(f64 mass, f64 step, const vec64 &potential, mat64 &result);

		void matrix(f64 mass, f64 step, const vec<mat64> &potential, mat64 &result);

		struct basis {
			mut<u32> J;
			mut<u32> v;
			mut<u32> j;
			mut<u32> l;
			mut<s32> p;
			mut<u32> comp;
			mut<u32> n_min;
			mut<f64> norm;
			mut<f64> r_min;
			mut<f64> r_max;
			mut<f64> r_step;
			mut<f64> eigenval;
			vec64 eigenvec;

			inline basis(usize count = 0):
				J(0), v(0), j(0), l(0), p(0), comp(0), n_min(0), norm(1.0), r_min(0.0), r_max(0.0), r_step(0.0), eigenval(0.0), eigenvec(count)
			{
			}

			inline void resize()
			{
				usize count = as_usize((this->r_max - this->r_min)/this->r_step);

				if (count != this->eigenvec.length()) {
					this->eigenvec.resize(count);
				}
			}

			inline f64 operator[](usize n) const
			{
				return this->norm*this->eigenvec[n];
			}
		};

		u32 is_valid(file::input &buf);

		void load_basis(u32 n, file::input &buf, basis &data);
	}
#endif
