#if !defined(STRING_HEADER)
	#define STRING_HEADER
	#include "types.h"
	#include "vector.h"

	#if !defined(DEFAULT_STRING_LENGTH)
		#define DEFAULT_STRING_LENGTH 1023
	#endif

	#if !defined(REALLOC_LENGTH_LIMIT)
		#define REALLOC_LENGTH_LIMIT 24
	#endif

	#if !defined(DEFAULT_FMT_PADDING)
		#define DEFAULT_FMT_PADDING 1
	#endif

	using str = Vec<char>;

	// NOTE: A forward declaration is used below to avoid including file.h and mpi.h
	// here, since these are not part of the essentials.h header. Both file::Input
	// and mpi::Frontend requires privileges to write the internal buffer of a string.

	namespace file {
		class Input;
	}

	namespace mpi {
		class Frontend;
	}

	class String {
		public:
		inline String(usize capacity = DEFAULT_STRING_LENGTH): buf(capacity + 1), end(0), begin(0)
		{
		}

		inline String(String &&other): buf(other.buf.move()), end(other.end), begin(other.begin)
		{
			other.end = other.begin = 0;
		}

		inline String(c_str other): buf(DEFAULT_STRING_LENGTH + 1), end(0), begin(0)
		{
			*this += other;
		}

		inline usize capacity() const
		{
			return this->buf.length();
		}

		inline usize length() const
		{
			return (this->end - this->begin);
		}

		inline void clear()
		{
			this->end = this->begin = this->buf[0] = 0;
		}

		inline c_str as_cstr() const
		{
			return &this->buf[this->begin];
		}

		inline String move()
		{
			return String(*this);
		}

		void left_trim()
		{
			while ((this->buf[this->begin] == ' ') && (this->begin < this->end)) {
				++this->begin;
			}
		}

		void right_trim()
		{
			while ((this->buf[this->end - 1] == ' ') && (this->end > this->begin)) {
				--this->end;
			}

			this->buf[this->end] = '\0';
		}

		inline void trim()
		{
			this->left_trim();
			this->right_trim();
		}

		template<u8 PAD = DEFAULT_FMT_PADDING, typename T>
		void append(const T val)
		{
			if constexpr(is_cstr<T>()) {
				usize len = std::strlen(val);
				this->check_avail_capacity(len, len);
			} else {
				this->check_avail_capacity();
			}

			this->end += as_usize(std::snprintf(&this->buf[this->end], (this->capacity() - this->end), type_fmt<T>(), PAD, val));
		}

		template<u8 PAD = DEFAULT_FMT_PADDING, typename T, typename... Ts>
		void append(const T first, const Ts... remainder)
		{
			this->append<PAD>(first);
			this->append<PAD>(remainder...);
		}

		inline void operator+=(c_str rhs)
		{
			this->append(rhs);
		}

		inline void operator+=(const bool rhs)
		{
			this->append(rhs? "true" : "false");
		}

		inline void operator+=(u8 rhs)
		{
			this->append(rhs);
		}

		inline void operator+=(u16 rhs)
		{
			this->append(rhs);
		}

		inline void operator+=(u32 rhs)
		{
			this->append(rhs);
		}

		inline void operator+=(u64 rhs)
		{
			this->append(rhs);
		}

		inline void operator+=(s8 rhs)
		{
			this->append(rhs);
		}

		inline void operator+=(s16 rhs)
		{
			this->append(rhs);
		}

		inline void operator+=(s32 rhs)
		{
			this->append(rhs);
		}

		inline void operator+=(s64 rhs)
		{
			this->append(rhs);
		}

		inline void operator+=(const char rhs)
		{
			this->append(rhs);
		}

		inline void operator+=(f32 rhs)
		{
			this->append(rhs);
		}

		inline void operator+=(f64 rhs)
		{
			this->append(rhs);
		}

		inline void operator+=(f128 rhs)
		{
			this->append(rhs);
		}

		inline void operator+=(c32 rhs)
		{
			this->append(rhs.real(), "  ", rhs.imag());
		}

		inline void operator+=(c64 rhs)
		{
			this->append(rhs.real(), "  ", rhs.imag());
		}

		inline void operator+=(String &rhs)
		{
			this->append(rhs.as_cstr());
		}

		inline void operator=(c_str rhs)
		{
			this->clear();
			this->append(rhs);
		}

		inline void operator=(const bool rhs)
		{
			this->clear();
			this->append(rhs? "true" : "false");
		}

		inline void operator=(u8 rhs)
		{
			this->clear();
			this->append(rhs);
		}

		inline void operator=(u16 rhs)
		{
			this->clear();
			this->append(rhs);
		}

		inline void operator=(u32 rhs)
		{
			this->clear();
			this->append(rhs);
		}

		inline void operator=(u64 rhs)
		{
			this->clear();
			this->append(rhs);
		}

		inline void operator=(s8 rhs)
		{
			this->clear();
			this->append(rhs);
		}

		inline void operator=(s16 rhs)
		{
			this->clear();
			this->append(rhs);
		}

		inline void operator=(s32 rhs)
		{
			this->clear();
			this->append(rhs);
		}

		inline void operator=(s64 rhs)
		{
			this->clear();
			this->append(rhs);
		}

		inline void operator=(const char rhs)
		{
			this->clear();
			this->append(rhs);
		}

		inline void operator=(f32 rhs)
		{
			this->clear();
			this->append(rhs);
		}

		inline void operator=(f64 rhs)
		{
			this->clear();
			this->append(rhs);
		}

		inline void operator=(f128 rhs)
		{
			this->clear();
			this->append(rhs);
		}

		inline void operator=(c32 rhs)
		{
			this->clear();
			this->append(rhs.real(), "  ", rhs.imag());
		}

		inline void operator=(c64 rhs)
		{
			this->clear();
			this->append(rhs.real(), "  ", rhs.imag());
		}

		void operator=(String &rhs)
		{
			this->end = rhs.end;
			this->begin = rhs.begin;
			this->buf.swap(rhs.buf);
			rhs.clear();
		}

		void operator=(String &&rhs)
		{
			this->end = rhs.end;
			this->begin = rhs.begin;
			this->buf.swap(rhs.buf);
		}

		inline char operator[](usize n) const
		{
			usize offset = this->begin + n;
			return (offset < this->end? this->buf[offset] : '\0');
		}

		inline void fill(const char c = ' ')
		{
			std::memset(this->as_ptr(), c, this->length());
		}

		void resize(usize count, const char c = ' ')
		{
			usize new_end = this->begin + count;

			if (new_end > this->capacity()) {
				this->reallocate(new_end);
			}

			if (new_end > this->end) {
				// NOTE: We preserve the current string, if any, and fill only
				// the additional chunk of characters.
				std::memset(&this->buf[this->end], c, (new_end - this->end));
			}

			this->end = new_end;
			this->buf[new_end] = '\0';
		}

		private:
		str buf;
		mut<usize> end;
		mut<usize> begin;

		inline char* as_ptr() const
		{
			return &this->buf[this->begin];
		}

		inline void reallocate(usize count)
		{
			this->buf.resize(count + 1);
		}

		void check_avail_capacity(usize count = DEFAULT_STRING_LENGTH, usize lim = REALLOC_LENGTH_LIMIT)
		{
			usize buf_len = this->capacity();

			if ((buf_len - this->end) < lim) {
				this->reallocate(2*buf_len > count? buf_len + 2*buf_len : buf_len + count);
			}
		}

		inline String(String &other): buf(other.buf.move()), end(other.end), begin(other.begin)
		{
		}

		friend class file::Input;
		friend class mpi::Frontend;
	};

	#undef DEFAULT_STRING_LENGTH
	#undef REALLOC_LENGTH_LIMIT
	#undef DEFAULT_FMT_PADDING
#endif
