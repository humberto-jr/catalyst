#if !defined(LIBBLAS_HEADER)
	#define LIBBLAS_HEADER
	#include "essentials.h"

	// NOTE: This module wraps the boilerplate code required to call the various implementations
	// of the BLAS Fortran library. This is done through the collection of C-bindings known as
	// CBLAS. The default CBLAS and BLAS are those provided by GSL. Others can be set by using
	// the macros USE_*, e.g., USE_MKL, USE_LAPACK etc. If, however, USE_CUDA is set, then the
	// cuBLAS library and GPUs can be used by calling the API from the libcuda.h header file.
	// This module only regards host-side implementations of BLAS. The BLAS functions are only
	// added here as they are needed throughout the codebase.

	#if defined(USE_MKL)
		#include <mkl.h>
		#define BLAS_BACKEND_NAME blas::Backend::mkl
	#elif defined(USE_LAPACKE)
		#include <cblas.h>
		#define BLAS_BACKEND_NAME blas::Backend::lapack
	#else
		#include "libgsl.h"
		#define BLAS_BACKEND_NAME blas::Backend::gsl
	#endif

	namespace blas {
		enum class Backend: u8 {
			gsl,
			mkl,
			lapack
		};

		static constexpr blas::Backend BACKEND = BLAS_BACKEND_NAME;

		static CBLAS_TRANSPOSE backend_transpose_enum(const char op)
		{
			switch (op) {
				case 'n':
				case 'N':
				return CblasNoTrans;

				case 't':
				case 'T':
				return CblasTrans;

				case 'c':
				case 'C':
				return CblasConjTrans;

				default:
				print::error(WHERE, "Invalid CBLAS transpose operation ", op);
			}

			// NOTE: Unreachable.
			return CblasNoTrans;
		}

		template<typename T>
		static void gemv(char transa,
		                 usize m, usize n,
		                 const T a[], usize lda, const T x[], usize incx,
		                 T y[], usize incy, const T alpha = 1.0, const T beta = 0.0)
		{
			assert(a != nullptr);
			assert(x != nullptr);
			assert(y != nullptr);

			const auto op_a = blas::backend_transpose_enum(transa);

			if constexpr(is_f32<T>()) {
				cblas_sgemv(CblasRowMajor, op_a, as_s32(m), as_s32(n),
				            alpha, a, as_s32(lda), x, as_s32(incx), beta, y, as_s32(incy));
			} else if constexpr(is_f64<T>()) {
				cblas_dgemv(CblasRowMajor, op_a, as_s32(m), as_s32(n),
				            alpha, a, as_s32(lda), x, as_s32(incx), beta, y, as_s32(incy));
			} else if constexpr(is_c32<T>()) {
				cblas_cgemv(CblasRowMajor, op_a, as_s32(m), as_s32(n),
				            alpha, a, as_s32(lda), x, as_s32(incx), beta, y, as_s32(incy));
			} else if constexpr(is_c64<T>()) {
				cblas_zgemv(CblasRowMajor, op_a, as_s32(m), as_s32(n),
				            alpha, a, as_s32(lda), x, as_s32(incx), beta, y, as_s32(incy));
			} else {
				print::error(WHERE, "Invalid generic type T = ", type_name<T>(), "; expected T = f32 or f64 or c32 or c64");
			}
		}

		template<typename T>
		static void gemv(const char transa,
		                 const Mat<T> &a, const Vec<T> &x, Vec<T> &y, const T alpha = 1.0, const T beta = 0.0)
		{
			// NOTE: To read as if matrix A is not transposed.
			const bool not_a = (transa == 'n') || (transa == 'N');

			if (not_a) {
				assert(x.length() == a.cols());
				assert(y.length() == a.rows());
			} else {
				assert(x.length() == a.rows());
				assert(y.length() == a.cols());
			}

			blas::gemv(transa, a.rows(), a.cols(), &a[0], a.rows(), &x[0], 1u, &y[0], 1u, alpha, beta);
		}

		template<typename T>
		static void gemm(char transa, char transb,
		                 usize m, usize n, usize k,
		                 const T a[], usize lda, const T b[], usize ldb,
		                 T c[], usize ldc, const T alpha = 1.0, const T beta = 0.0)
		{
			assert(a != nullptr);
			assert(b != nullptr);
			assert(c != nullptr);

			const auto op_a = blas::backend_transpose_enum(transa);
			const auto op_b = blas::backend_transpose_enum(transb);

			if constexpr(is_f32<T>()) {
				cblas_sgemm(CblasRowMajor, op_a, op_b, as_s32(m), as_s32(n), as_s32(k),
					        alpha, a, as_s32(lda), b, as_s32(ldb), beta, c, as_s32(ldc));
			} else if constexpr(is_f64<T>()) {
				cblas_dgemm(CblasRowMajor, op_a, op_b, as_s32(m), as_s32(n), as_s32(k),
					        alpha, a, as_s32(lda), b, as_s32(ldb), beta, c, as_s32(ldc));
			} else if constexpr(is_c32<T>()) {
				cblas_cgemm(CblasRowMajor, op_a, op_b, as_s32(m), as_s32(n), as_s32(k),
					        alpha, a, as_s32(lda), b, as_s32(ldb), beta, c, as_s32(ldc));
			} else if constexpr(is_c64<T>()) {
				cblas_zgemm(CblasRowMajor, op_a, op_b, as_s32(m), as_s32(n), as_s32(k),
					        alpha, a, as_s32(lda), b, as_s32(ldb), beta, c, as_s32(ldc));
			} else {
				print::error(WHERE, "Invalid generic type T = ", type_name<T>(), "; expected T = f32 or f64 or c32 or c64");
			}
		}

		template<typename T>
		static void gemm(const char transa, const char transb,
		                 const Mat<T> &a, const Mat<T> &b, Mat<T> &c, const T alpha = 1.0, const T beta = 0.0)
		{
			// NOTE: Definitions of m, n, k, lda, ldb, and ldc can become somewhat confusing, thus the ones used
			// below are taken from Section 2.7.1 of https://docs.nvidia.com/cuda/cublas/index.html#cublas-t-gemm

			// NOTE: To read as if matrix A (B) is not transposed.
			const bool not_a = (transa == 'n') || (transa == 'N');
			const bool not_b = (transb == 'n') || (transb == 'N');

			usize m = c.rows();
			usize n = c.cols();
			usize k = (not_a? a.cols() : a.rows());

			usize lda = (not_a? m : k);
			usize ldb = (not_b? k : n);
			usize ldc = m;

			if (not_a) {
				assert(a.length() >= lda*k);
			} else {
				assert(a.length() >= lda*m);
			}

			if (not_b) {
				assert(b.length() >= ldb*n);
			} else {
				assert(b.length() >= ldb*k);
			}

			blas::gemm(transa, transb, m, n, k,
			           &a[0], lda, &b[0], ldb, &c[0], ldc, alpha, beta);
		}
	}

	#undef BLAS_BACKEND_NAME
#endif
