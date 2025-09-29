#pragma once

#if defined(__cplusplus)
	// C89 to C95
	#include <cmath>
	#include <ctime>
	#include <cfloat>
	#include <cwchar>
	#include <cerrno>
	#include <cstdio>
	#include <cctype>
	#include <cassert>
	#include <ciso646>
	#include <cwctype>
	#include <climits>
	#include <clocale>
	#include <csetjmp>
	#include <csignal>
	#include <cstdarg>
	#include <cstddef>
	#include <cstdlib>
	#include <cstring>

	// C POSIX library
	#include <unistd.h>

	// C99
	#include <cfenv>
	#include <cstdint>
	#include <ctgmath>
	#include <cstdbool>
	#include <cinttypes>

	// C11 and beyond
	#include <cuchar>
#else
	/* C89 to C95 */
	#include <math.h>
	#include <time.h>
	#include <float.h>
	#include <wchar.h>
	#include <errno.h>
	#include <stdio.h>
	#include <ctype.h>
	#include <assert.h>
	#include <iso646.h>
	#include <wctype.h>
	#include <limits.h>
	#include <locale.h>
	#include <setjmp.h>
	#include <signal.h>
	#include <stdarg.h>
	#include <stddef.h>
	#include <stdlib.h>
	#include <string.h>

	/* C POSIX library */
	#include <unistd.h>

	/* C99 */
	#if (__STDC_VERSION__ >= 199901L)
		#include <fenv.h>
		#include <stdint.h>
		#include <tgmath.h>
		#include <complex.h>
		#include <stdbool.h>
		#include <inttypes.h>
	#endif

	/* C11 and beyond */
	#if (__STDC_VERSION__ > 199901L)
		#include <uchar.h>
		#include <stdalign.h>
		#include <stdnoreturn.h>

		#if !defined(_OPENMP)
			#include <stdatomic.h>
		#endif

		#if !defined(__STDC_NO_THREADS__)
			#include <threads.h>
		#endif
	#endif
#endif
