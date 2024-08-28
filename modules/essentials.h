#if !defined(ESSENTIALS_HEADER)
	#define ESSENTIALS_HEADER
	#include <omp.h>
	#include "libc.h"
	#include "types.h"

	#if defined(_OPENMP) && !defined(MAX_HOST_THREAD_COUNT)
		#define MAX_HOST_THREAD_COUNT 256u
	#else
		#define MAX_HOST_THREAD_COUNT 1u
	#endif

	[[maybe_unused]]
	static inline u32 thread_count()
	{
		#if defined(_OPENMP)
			// NOTE: This must be less than or equal to
			// the value set in MAX_HOST_THREAD_COUNT.
			return as_u32(omp_get_num_threads());
		#else
			return 1u;
		#endif
	}

	[[maybe_unused]]
	static inline u32 thread_id()
	{
		#if defined(_OPENMP)
			return as_u32(omp_get_thread_num());
		#else
			return 0u;
		#endif
	}

	#include "print.h"
	#include "vector.h"
	#include "string.h"
	#include "matrix.h"
#endif
