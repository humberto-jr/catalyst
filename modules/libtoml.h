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

	// NOTE: The toml namespace is now available. The toml++ documentation can
	// be found at https://marzer.github.io/tomlplusplus/namespacetoml.html
	#include "../vendors/toml.hpp"
#endif
