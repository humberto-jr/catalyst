#if !defined(LIBTOML_HEADER)
	#define LIBTOML_HEADER
	#include "essentials.h"

	#define TOML_EXCEPTIONS 0

	#define TOML_ENABLE_FORMATTERS 0

	#define TOML_ASSERT(expr)                                    \
	{                                                            \
	  if (!(expr)) {                                             \
	    print::error(WHERE, "toml++ assertion failed: ", #expr); \
	  }                                                          \
	}

	#include "../vendors/toml.hpp"
#endif
