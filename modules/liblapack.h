#if !defined(LIBLAPACK_HEADER)
	#define LIBLAPACK_HEADER
	#include "essentials.h"

	// NOTE: This module wraps the boilerplate code required to call the various implementations
	// of the LAPACK Fortran library. This is done through the collection of C-bindings known as
	// LAPACKE. Other implementations can be set by using the macros USE_*, e.g., USE_MKL,
	// USE_LAPACK etc. Otherwise, the same functionality is emulated using the linalg module of
	// GSL. The LAPACK functions are only added here as they are needed throughout the codebase.

	#if !defined(LAPACK_DISABLE_NAN_CHECK)
		#define LAPACK_DISABLE_NAN_CHECK
	#endif

	#if defined(USE_MKL)
		#include <mkl_lapacke.h>
		#define LAPACK_BACKEND_NAME lapack::backend::mkl
	#elif defined(USE_LAPACKE)
		#include <lapacke.h>
		#define LAPACK_BACKEND_NAME lapack::backend::lapacke
	#else
		#include "libgsl.h"
		#define LAPACK_BACKEND_NAME lapack::backend::gsl
	#endif

	#define CHECK_LAPACKE_ERROR(name, code)                              \
	{                                                                    \
	  if ((code) != 0) {                                                 \
	    print::error(WHERE, (name), " failed with error code ", (code)); \
	  }                                                                  \
	}

	namespace lapack {
		enum class backend: u8 {
			gsl,
			mkl,
			lapacke
		};

		static constexpr lapack::backend BACKEND = LAPACK_BACKEND_NAME;

		static constexpr c_str backend_name()
		{
			switch (lapack::BACKEND) {
				case lapack::backend::gsl:     return "GNU Scientific Library\0";
				case lapack::backend::mkl:     return "Intel Math Kernel Library\0";
				case lapack::backend::lapacke: return "LAPACKE\0";
				default:                       return "Unknown\0";
			}
		}

		template<typename T>
		static void syev(const char jobz, const char uplo, usize n, T a[], T w[])
		{
			assert(a != nullptr);
			assert(w != nullptr);

			// NOTE: Since this routine only handles symmetric n-by-n matrices,
			// we ignore the lda parameter, i.e., lda = n by default.
			s32 lda = as_s32(n);

			#if defined(USE_MKL) || defined(USE_LAPACKE)
				// NOTE:
				// https://netlib.org/lapack/explore-html-3.6.1/d2/d8a/group__double_s_yeigen_ga442c43fca5493590f8f26cf42fed4044.html

				#if defined(USE_MKL)
					LAPACKE_set_nancheck(0);
				#endif

				if constexpr(is_f32<T>()) {
					auto info = LAPACKE_ssyev(LAPACK_ROW_MAJOR, jobz, uplo, lda, a, lda, w);
					CHECK_LAPACKE_ERROR("LAPACKE_ssyev()", info)
				} else if constexpr(is_f64<T>()) {
					auto info = LAPACKE_dsyev(LAPACK_ROW_MAJOR, jobz, uplo, lda, a, lda, w);
					CHECK_LAPACKE_ERROR("LAPACKE_dsyev()", info)
				} else {
					print::error(WHERE, "Invalid generic type T = ", type_name<T>(), "; expected T = f32 or f64");
				}
			#else
				// TODO:
				static_assert(is_f64<T>(), "Only T = f64 is possible when GSL is used as backend");

				if ((uplo != 'l') && (uplo != 'L')) {
					print::error(WHERE, "uplo = l is expected when GSL is used as backend");
				}

				auto a_view = gsl_matrix_view_array(a, lda, lda);

				auto w_view = gsl_vector_view_array(w, lda);

				auto *eigenvec = gsl_matrix_alloc(lda, lda);

				auto *work = gsl_eigen_symmv_alloc(lda);

				auto info = gsl_eigen_symmv(&a_view.matrix, &w_view.vector, eigenvec, work);

				CHECK_LAPACKE_ERROR("gsl_eigen_symmv()", info)

				gsl_eigen_symmv_free(work);

				info = gsl_eigen_symmv_sort(&w_view.vector, eigenvec, GSL_EIGEN_SORT_VAL_ASC);

				CHECK_LAPACKE_ERROR("gsl_eigen_symmv_sort()", info)

				if ((jobz == 'v') || (jobz == 'V')) {
					gsl_matrix_memcpy(&a_view.matrix, eigenvec);
				}

				gsl_matrix_free(eigenvec);
			#endif
		}

		template<typename T>
		static void syev(mat<T> &eigenvec, vec<T> &eigenval)
		{
			usize n = eigenvec.rows();

			assert(eigenvec.cols() == n);
			assert(eigenval.length() == n);

			lapack::syev('v', 'l', n, &eigenvec[0], &eigenval[0]);
		}

		template<typename T>
		static void sytri(const char uplo, usize n, T a[], mut<s32> ipiv[])
		{
			#if defined(USE_MKL) || defined(USE_LAPACKE)
				// NOTE:
				// https://www.netlib.org/lapack/explore-html-3.6.1/d3/db6/group__double_s_ycomputational_ga75e09b4299b7955044a3bbf84c46b593.html

				#if defined(USE_MKL)
					LAPACKE_set_nancheck(0);
				#endif

				// NOTE: From mkl_lapacke.h and mkl_types.h: When using MKL ILP64 integer types,
				// lapack_int = MKL_INT = MKL_INT64 = long long int. Thus, it may not match the
				// definition of s32.
				auto ipiv_ptr = static_cast<lapack_int*>(&ipiv[0]);

				// NOTE: Since this routine only handles symmetric n-by-n matrices,
				// we ignore the lda parameter, i.e., lda = n by default.
				s32 lda = as_s32(n);

				if constexpr(is_f32<T>()) {
					auto info = LAPACKE_ssytrf(LAPACK_ROW_MAJOR, uplo, lda, a, lda, ipiv_ptr);
					CHECK_LAPACKE_ERROR("LAPACKE_ssytrf()", info)

					info = LAPACKE_ssytri(LAPACK_ROW_MAJOR, uplo, lda, a, lda, ipiv_ptr);
					CHECK_LAPACKE_ERROR("LAPACKE_ssytri()", info)
				} else if constexpr(is_f64<T>()) {
					auto info = LAPACKE_dsytrf(LAPACK_ROW_MAJOR, uplo, lda, a, lda, ipiv_ptr);
					CHECK_LAPACKE_ERROR("LAPACKE_dsytrf()", info)

					info = LAPACKE_dsytri(LAPACK_ROW_MAJOR, uplo, lda, a, lda, ipiv_ptr);
					CHECK_LAPACKE_ERROR("LAPACKE_dsytri()", info)
				} else if constexpr(is_c32<T>()) {
					auto info = LAPACKE_csytrf(LAPACK_ROW_MAJOR, uplo, lda, a, lda, ipiv_ptr);
					CHECK_LAPACKE_ERROR("LAPACKE_csytrf()", info)

					info = LAPACKE_csytri(LAPACK_ROW_MAJOR, uplo, lda, a, lda, ipiv_ptr);
					CHECK_LAPACKE_ERROR("LAPACKE_csytri()", info)
				} else if constexpr(is_c64<T>()) {
					auto info = LAPACKE_zsytrf(LAPACK_ROW_MAJOR, uplo, lda, a, lda, ipiv_ptr);
					CHECK_LAPACKE_ERROR("LAPACKE_zsytrf()", info)

					info = LAPACKE_zsytri(LAPACK_ROW_MAJOR, uplo, lda, a, lda, ipiv_ptr);
					CHECK_LAPACKE_ERROR("LAPACKE_zsytri()", info)
				} else {
					print::error(WHERE, "Invalid generic type T = ", type_name<T>(), "; expected T = f32 or f64 or c32 or c64");
				}
			#else
				// TODO:
				static_assert(is_f64<T>(), "Only T = f64 is possible when GSL is used as backend");

				vec<f64> a_copy(n*n);

				for (mut<usize> n = 0; n < a_copy.length(); ++n) {
					a_copy[n] = a[n];
				}

				gsl_permutation *p = gsl_permutation_alloc(n);

				gsl_matrix_view a_inv = gsl_matrix_view_array(&a[0], n, n);

				gsl_matrix_view a_view = gsl_matrix_view_array(&a_copy[0], n, n);

				mut<s32> sign = 0;
				auto info = gsl_linalg_LU_decomp(&a_view.matrix, p, &sign);

				CHECK_LAPACKE_ERROR("gsl_linalg_LU_decomp()", info)

				info = gsl_linalg_LU_invert(&a_view.matrix, p, &a_inv.matrix);

				CHECK_LAPACKE_ERROR("gsl_linalg_LU_invert()", info)

				gsl_permutation_free(p);
			#endif
		}

		template<typename T>
		static void sytri(mat<T> &a, vec<s32> &ipiv)
		{
			usize n = a.rows();

			assert(a.cols() == n);
			assert(ipiv.length() == n);

			lapack::sytri('u', n, &a[0], &ipiv[0]);

			#if defined(USE_MKL) || defined(USE_LAPACKE)
				// NOTE: Up to this point only the upper triangular part is actually
				// inverted (uplo = 'u'). Thus, we have to copy the result into the
				// lower one for consistency.

				for (mut<usize> row = 0; row < a.rows(); ++row) {
					for (mut<usize> col = (row + 1); col < a.cols(); ++col) {
						a(col, row) = a(row, col);
					}
				}
			#endif
		}

		template<typename T>
		static inline void sytri(mat<T> &a)
		{
			vec<s32> ipiv(a.rows());
			lapack::sytri(a, ipiv);
		}

		template<typename T>
		static void gesv(usize n, usize nrhs, T a[], mut<s32> ipiv[], T b[])
		{
			assert(a != nullptr);
			assert(b != nullptr);
			assert(ipiv != nullptr);

			// NOTE: The matrix A is n-by-n and B is n-by-nrhs in the original LAPACK.
			// Thus, we ignore the lda and ldb parameters, i.e., lda = ldb = n by default.
			s32 lda = as_s32(n);
			s32 ldb = lda;

			#if defined(USE_MKL) || defined(USE_LAPACKE)
				// NOTE:
				// https://netlib.org/lapack/explore-html-3.6.1/d7/d3b/group__double_g_esolve_ga5ee879032a8365897c3ba91e3dc8d512.html

				#if defined(USE_MKL)
					LAPACKE_set_nancheck(0);
				#endif

				if constexpr(is_f32<T>()) {
					auto info = LAPACKE_sgesv(LAPACK_ROW_MAJOR, lda, as_s32(nrhs), a, lda, ipiv, b, ldb);
					CHECK_LAPACKE_ERROR("LAPACKE_sgesv()", info)
				} else if constexpr(is_f64<T>()) {
					auto info = LAPACKE_dgesv(LAPACK_ROW_MAJOR, lda, as_s32(nrhs), a, lda, ipiv, b, ldb);
					CHECK_LAPACKE_ERROR("LAPACKE_dgesv()", info)
				} else if constexpr(is_c32<T>()) {
					auto info = LAPACKE_cgesv(LAPACK_ROW_MAJOR, lda, as_s32(nrhs), a, lda, ipiv, b, ldb);
					CHECK_LAPACKE_ERROR("LAPACKE_cgesv()", info)
				} else if constexpr(is_c64<T>()) {
					auto info = LAPACKE_zgesv(LAPACK_ROW_MAJOR, lda, as_s32(nrhs), a, lda, ipiv, b, ldb);
					CHECK_LAPACKE_ERROR("LAPACKE_zgesv()", info)
				} else {
					print::error(WHERE, "Invalid generic type T = ", type_name<T>(), "; expected T = f32 or f64 or c32 or c64");
				}
			#else
				// TODO:
				print::error(WHERE, "Missing the implementation of LAPACK gesv() routines when GSL is used as backend");
			#endif
		}

		template<typename T>
		static void gesv(mat<T> &a, vec<s32> &ipiv, mat<T> &b)
		{
			usize n = a.rows();
			usize nrhs = b.cols();

			assert(a.cols() == n);
			assert(b.rows() == n);
			assert(ipiv.length() == n);

			lapack::gesv(n, nrhs, &a[0], &ipiv[0], &b[0]);
		}

		template<typename T>
		static void gesv(mat<T> &a, mat<T> &b)
		{
			usize n = a.rows();
			usize nrhs = b.cols();

			assert(a.cols() == n);
			assert(b.rows() == n);
			vec<s32> ipiv(n);

			lapack::gesv(n, nrhs, &a[0], &ipiv[0], &b[0]);
		}
	}

	#undef CHECK_LAPACKE_ERROR
	#undef LAPACK_BACKEND_NAME
#endif
