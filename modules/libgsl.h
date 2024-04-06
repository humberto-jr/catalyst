#if !defined(LIBGSL_HEADER)
	#define LIBGSL_HEADER
	#include "libc.h"

	#if !defined(HAVE_INLINE)
		#define HAVE_INLINE
	#endif

	#if !defined(__GNUC__) && !defined(GSL_C99_INLINE)
		#define GSL_C99_INLINE
	#endif

	// Error handling
	#include <gsl/gsl_errno.h>

	// Basic functions
	#include <gsl/gsl_math.h>

	// Special functions
	#include <gsl/gsl_sf_bessel.h>
	#include <gsl/gsl_sf_legendre.h>
	#include <gsl/gsl_sf_coupling.h>

	// Random numbers generation
	#include <gsl/gsl_rng.h>

	// Matrices and vectors
	#include <gsl/gsl_vector.h>
	#include <gsl/gsl_matrix.h>

	// BLAS and linear algebra
	#include <gsl/gsl_cblas.h>
	#include <gsl/gsl_eigen.h>
	#include <gsl/gsl_linalg.h>

	// Monte Carlo integration
	#include <gsl/gsl_monte_plain.h>
	#include <gsl/gsl_monte_miser.h>
	#include <gsl/gsl_monte_vegas.h>

	// Interpolation
	#include <gsl/gsl_interp.h>
	#include <gsl/gsl_spline.h>

	// Numerical integration
	#include <gsl/gsl_integration.h>

	// NOTE: For compatibility with MKL and LAPACKE.
	typedef enum CBLAS_TRANSPOSE CBLAS_TRANSPOSE;
#endif
