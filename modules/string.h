#if !defined(STRING_HEADER)
	#define STRING_HEADER
	#include "types.h"
	#include "vector.h"

	#if !defined(DEFAULT_STRING_LENGTH)
		#define DEFAULT_STRING_LENGTH 1023
	#endif

	using str = vec<char>;

	// NOTE: A forward declaration is used below to avoid including file.h and mpi.h
	// here, since these are not part of the essentials.h header. Both file::input
	// and mpi::frontend requires privileges to write the internal buffer of a string.

	namespace file {
		class input;
	}

	namespace mpi {
		class frontend;
	}

	class string {
		public:
		inline string(usize capacity = DEFAULT_STRING_LENGTH): buf(capacity + 1), end(0), begin(0)
		{
			this->buf[0] = '\0';
		}

		inline string(string &&other): buf(other.buf.move()), end(other.end), begin(other.begin)
		{
			other.end = other.begin = 0;
		}

		inline string(c_str other): buf(DEFAULT_STRING_LENGTH + 1), end(0), begin(0)
		{
			this->buf[0] = '\0';
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
			this->end = 0;
			this->begin = 0;
			this->buf[0] = '\0';
		}

		inline c_str as_cstr() const
		{
			return &this->buf[this->begin];
		}

		inline string move()
		{
			return string(*this);
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

		template<u8 PAD = 1, typename T>
		void append(const T val)
		{
			usize buf_len = DEFAULT_STRING_LENGTH + 1;

			char buf[buf_len] = {'\0'};

			s32 info = std::snprintf(&buf[0], buf_len, type_fmt<T>(), PAD, val);
			assert(info > -1);

			*this += static_cast<c_str>(&buf[0]);
		}

		void operator+=(c_str rhs)
		{
			if (this->capacity() == 0) {
				this->resize(DEFAULT_STRING_LENGTH + 1);
			}

			mut<usize> n = 0;
			mut<usize> max_len = this->capacity() - 1;

			while (rhs[n] != '\0') {
				usize offset = this->end + n;

				this->buf[offset] = rhs[n];

				if (offset == max_len) {
					this->resize(max_len + 2*max_len);

					max_len = this->capacity() - 1;
				}

				++n;
			}

			this->end += n;
			this->buf[this->end] = '\0';
		}

		inline void operator+=(string &rhs)
		{
			*this += rhs.as_cstr();
		}

		template<typename T>
		void operator+=(const T rhs)
		{
			this->append(rhs);
		}

		inline void operator=(c_str rhs)
		{
			 this->clear();
			*this += rhs;
		}

		void operator=(string &rhs)
		{
			this->clear();
			this->end = rhs.end;
			this->begin = rhs.begin;
			this->buf.swap(rhs.buf);
		}

		template<typename T>
		void operator=(const T rhs)
		{
			this->clear();
			this->append(rhs);
		}

		string operator+(string &rhs)
		{
			string result(this->capacity() + rhs.capacity() + 1);
			result += this->as_cstr();
			result += rhs.as_cstr();
			return result;
		}

		inline char operator[](usize n) const
		{
			usize offset = this->begin + n;
			return (offset < this->end? this->buf[offset] : '\0');
		}

		private:
		str buf;
		mut<usize> end;
		mut<usize> begin;

		inline char* as_ptr() const
		{
			return &this->buf[this->begin];
		}

		inline void resize(usize count)
		{
			this->buf.resize(count);
		}

		// NOTE: See the note on the private copy-constructor of vector.
		inline string(string &other): buf(other.buf.move()), end(other.end), begin(other.begin)
		{
		}

		friend class file::input;
		friend class mpi::frontend;
	};

	#undef DEFAULT_STRING_LENGTH
#endif
