#if !defined(NUMEROV_HEADER)
	#define NUMEROV_HEADER
	#include "essentials.h"
	#include "liblapack.h"
	#include "fgh.h"

	namespace numerov {
		// NOTE: The first file format is intended for input coupling potentials,
		// the second for output Numerov ratio matrices and the third for S-matrices.
		constexpr u8 FORMAT_VERSION = 3;

		constexpr u32 MAGIC_NUMBER = 1701998454u;

		using basis = vec<fgh::basis>;

		struct potential {
			public:
			u32 n_min;
			f64 R_min;
			f64 R_max;
			f64 R_step;
			f64 mass;

			inline potential(u32 n_min, f64 R_min, f64 R_max, f64 R_step, f64 mass, mat<f64> &coupling, file::input &input):
				n_min(n_min), R_min(R_min), R_max(R_max), R_step(R_step), mass(mass), coupling(coupling.move()), input(input)
			{
			}

			const mat<f64>& operator[](u32 n);

			inline c_str filename() const
			{
				return this->input.filename.as_cstr();
			}

			private:
			mat<f64> coupling;
			file::input input;
		};

		numerov::basis open_basis_file(const string &filename);

		numerov::potential open(string &filename, u8 ver = 1);

		void renormalized(f64 mass,
		                  f64 step,
		                  f64 tot_energy,
		                  const mat<f64> &pot_energy,
		                  mat<f64> &workspace,
		                  mat<f64> &old_ratio,
		                  mat<f64> &new_ratio,
		                  lapack::frontend &lapack);

		usize build_react_matrix(f64 mass,
		                         f64 step,
		                         f64 R_max,
		                         f64 tot_energy,
		                         const mat<f64> &ratio,
		                         const numerov::basis &level,
		                         mat<f64> &k, lapack::frontend &lapack);

		void build_scatt_matrix(const mat<f64> &k,
		                        mat<f64> &re_s, mat<f64> &im_s, lapack::frontend &lapack);

		inline static f64 centrifugal_term(f64 l, f64 mass, f64 x)
		{
			return l*(l + 1.0)/(2.0*mass*x*x);
		}

		inline static f64 centrifugal_term(u32 l, f64 mass, f64 x)
		{
			return numerov::centrifugal_term(as_f64(l), mass, x);
		}
	}
#endif
