#if !defined(FGH_HEADER)
	#define FGH_HEADER
	#include "essentials.h"
	#include "file.h"

	namespace fgh {
		static constexpr u8 FORMAT_VERSION = 1;

		static constexpr u32 MAGIC_NUMBER = 464748u;

		void matrix(f64 mass, f64 step, const Vec<f64> &potential, Mat<f64> &result);

		void matrix(f64 mass, f64 step, const Vec<Mat<f64>> &potential, Mat<f64> &result);

		f64 norm(f64 step, const Vec<f64> &eigenvec);

		f64 centrifugal_term(const Range<f64> &r_list, const Vec<f64> &eigenvec);

		struct BasisEntry {
			mut<u32> J;
			mut<u32> v;
			mut<u32> n;
			mut<u32> j;
			mut<u32> l;
			mut<s32> p;
			mut<u32> c;
			mut<u8> spin_mult;
			mut<f64> norm;
			Range<f64> r_list;
			mut<f64> eigenval;
			Vec<f64> eigenvec;

			inline BasisEntry(usize count = 0):
				J(0), v(0), n(0), j(0), l(0), p(0), c(0), spin_mult(1), norm(1.0), r_list(0.0, 0.0, 0.0), eigenval(0.0), eigenvec(count)
			{
			}

			inline f64 operator[](usize n) const
			{
				return this->norm*this->eigenvec[n];
			}
		};

		class Basis {
			public:
			Basis(c_str filename, u8 fmt_ver = 1);

			const BasisEntry& operator[](usize index);

			inline usize count() const
			{
				return this->len;
			}

			struct Iterator {
				inline Iterator(fgh::Basis &owner): index(0), owner(owner)
				{
				}

				inline bool operator!=(usize max_len) const
				{
					return (this->index < max_len);
				}

				inline const fgh::BasisEntry& operator*()
				{
					return this->owner[this->index];
				}

				inline void operator++()
				{
					this->index += 1;
				}

				mut<usize> index;
				Basis &owner;
			};

			inline Basis::Iterator begin()
			{
				return Basis::Iterator(*this);
			}

			inline usize end() const
			{
				return this->count();
			}

			private:
			mut<usize> len;
			mut<usize> stride;
			file::Input input;
			fgh::BasisEntry entry;
		};
	}
#endif
