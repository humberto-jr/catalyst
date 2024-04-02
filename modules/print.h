#if !defined(PRINT_HEADER)
	#define PRINT_HEADER
	#include "types.h"

	#if !defined(DEFAULT_FMT_PADDING)
		#define DEFAULT_FMT_PADDING 1
	#endif

	#if !defined(DEFAULT_FMT_LENGTH)
		#define DEFAULT_FMT_LENGTH 1023
	#endif

	namespace print {
		// NOTE: The implementation of functions print::line() and print::error() ended up becoming complicated,
		// so a couple of comments on it are given here. The intent was to print a formatted line composed by "a,"
		// "b," and "c" (or more) with print::line(a, b, c) and without the somewhat cumbersome use of C++ std::cout
		// or the error-prone formattings of C printf(). This is accomplished by means of a variadic template where
		// each call to print::line() (and print::error()) is actually a set of recursive calls made by the compiler
		// in order to print each argument. However, in a multithreaded context, each recursive call may or may not
		// be interleaved by a call from another thread, producing lines made up of chunks of lines from many threads.
		// To avoid the problem, each call will store the partially formatted line in a C-string buffer, intrinsically
		// local to each thread, which will be printed only at the end of the call chain. The print::fmt struct is the
		// wrapper over the buffer and the boilerplate code needed to use it. Finally, the C format specifier of each
		// argument is deduced by the type_fmt() function from the types.h module.

		template<u8 PAD = DEFAULT_FMT_PADDING, usize LEN = DEFAULT_FMT_LENGTH>
		struct fmt {
			msize len;
			char buf[LEN + 1];

			inline fmt(): len(0), buf{'\0'}
			{
			}

			template<typename T>
			inline fmt(const T val): len(0), buf{'\0'}
			{
				*this += val;
			}

			inline usize capacity() const
			{
				return LEN;
			}

			inline void clear()
			{
				this->len = 0;
				this->buf[0] = '\0';
			}

			inline char* end()
			{
				return &this->buf[this->len];
			}

			inline c_str as_cstr() const
			{
				return &this->buf[0];
			}

			void flush(std::FILE *stream = stdout) const
			{
				#pragma omp critical(stream)
				std::fprintf(stream, "%s\n", this->as_cstr());
			}

			template<typename T>
			void operator+=(const T val)
			{
				usize max_len = this->capacity() - this->len + 1;

				s32 info = std::snprintf(this->end(), max_len, type_fmt<T>(), PAD, val);
				assert(info > -1);

				this->len += as_usize(info);
			}

			template<usize RHS_LEN>
			inline fmt<PAD, LEN + RHS_LEN> operator+(const fmt<PAD, RHS_LEN> &rhs) const
			{
				fmt<PAD, LEN + RHS_LEN> result(this->as_cstr());
				result += rhs.as_cstr();
				return result;
			}
		};

		[[maybe_unused]]
		static inline void line()
		{
			fmt<1, 1> blank;
			blank.flush();
		}

		template<u8 PAD, usize LEN>
		static void line(const fmt<PAD, LEN> &content)
		{
			content.flush();
		}

		template<u8 PAD, usize LEN, typename T>
		static void line(const fmt<PAD, LEN> &prev, T last)
		{
			fmt<PAD> end(last);
			line(prev + end);
		}

		template<u8 PAD, usize LEN, typename T, typename... Ts>
		static void line(const fmt<PAD, LEN> &prev, T first, Ts... remainder)
		{
			fmt<PAD> next(first);
			line(prev + next, remainder...);
		}

		template<u8 PAD = 1, typename T, typename... Ts>
		static void line(T first, Ts... remainder)
		{
			fmt<PAD> start(first);
			line(start, remainder...);
		}

		template<u8 PAD, usize LEN>
		static void error(const fmt<PAD, LEN> &content)
		{
			content.flush(stderr);
			std::exit(EXIT_FAILURE);
		}

		template<u8 PAD, usize LEN, typename T>
		static void error(const fmt<PAD, LEN> &prev, T last)
		{
			fmt<PAD> end(last);
			error(prev + end);
		}

		template<u8 PAD, usize LEN, typename T, typename... Ts>
		static void error(const fmt<PAD, LEN> &prev, T first, Ts... remainder)
		{
			fmt<PAD> next(first);
			error(prev + next, remainder...);
		}

		template<u8 PAD = 1, typename T, typename... Ts>
		static void error(T first, Ts... remainder)
		{
			fmt<PAD> start(first);
			error(start, remainder...);
		}

		[[maybe_unused]]
		static void timestamp()
		{
			auto now = std::time(nullptr);
			auto info = std::localtime(&now);

			fmt<127> stamp;
			stamp.len = std::strftime(&stamp.buf[0], 128, "# %B %d, %Y %I:%M:%S %p", info);

			stamp.flush();
		}

		[[maybe_unused]]
		static print::fmt<1, 255> error_location_label(c_str file, c_str function, u32 line, u32 thread)
		{
			print::fmt<1, 255> label;
			label += "# In ";
			label += file;
			label += ", ";
			label += function;
			label += "(), line ";
			label += line;
			label += ", thread ";
			label += thread;
			label += ": ";
			return label;
		}
	}

	#if defined(ESSENTIALS_HEADER)
		#define WHERE print::error_location_label(__FILE__, __func__, __LINE__, thread_id())
	#else
		#define WHERE print::error_location_label(__FILE__, __func__, __LINE__, 0u)
	#endif

	#undef DEFAULT_FMT_PADDING
	#undef DEFAULT_FMT_LENGTH
#endif
