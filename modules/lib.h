#if !defined(LIB_HEADER)
	#define LIB_HEADER
	#include "essentials.h"
	#include <optional>

	// NOTE: A POSIX library, may only be available on Unix-like systems.
	#include <dlfcn.h>

	// NOTE: This module is responsible for loading shared libraries *.so at runtime.
	// These must be compiled with the -fPIC (GNU toolchain) flag, or converted from
	// one or more object files *.o, which in turn are compiled with the -fPIC option.
	// The flags for specific compilers should be checked.

	class lib {
		public:
		inline lib(c_str filename):
			file(filename), handle(dlopen(filename, RTLD_LAZY | RTLD_LOCAL))
		{
		}

		inline lib(lib &&other):
			file(other.file.move()), handle(other.handle)
		{
			other.handle = nullptr;
		}

		inline bool is_loaded() const
		{
			return (this->handle != nullptr);
		}

		inline c_str filename() const
		{
			return this->file.as_cstr();
		}

		template<typename T>
		std::optional<T> find_symbol(c_str name)
		{
			// NOTE: C++ symbol names are mangled and won't load if the source
			// names are used. Thus, they should be declared as extern "C" for
			// C-style name mangling, which is well-defined. As for Fortran,
			// symbols may or may not have an underscore appended.
			auto symbol = dlsym(this->handle, name);

			if (symbol == nullptr) {
				return {};
			} else {
				// NOTE: Only C-style casts seem to work here.
				return (T) symbol;
			}
		}

		inline ~lib()
		{
			if (this->is_loaded()) {
				dlclose(this->handle);
			}
		}

		private:
		String file;
		void *handle;
	};
#endif
