#if !defined(ESSENTIALS_HEADER)
	#define ESSENTIALS_HEADER
	#include <omp.h>
	#include "libc.h"
	#include "types.h"

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
