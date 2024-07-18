#if !defined(NUMEROV_HEADER)
	#define NUMEROV_HEADER
	#include "essentials.h"
	#include "liblapack.h"
	#include "fgh.h"

	namespace numerov {
		using basis = vec<fgh::basis>;

		void renormalized(f64 mass,
		                  f64 step,
		                  f64 tot_energy,
		                  mat<f64> &pot_energy,
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
