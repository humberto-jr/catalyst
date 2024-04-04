#if !defined(STRING_HEADER)
	#define STRING_HEADER
	#include "types.h"
	#include "vector.h"

	#if !defined(DEFAULT_STRING_LENGTH)
		#define DEFAULT_STRING_LENGTH 1023
	#endif

	typedef vector<char> str;

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
			while (this->buf[this->end - 1] == ' ') {
				--this->end;
			}

			this->buf[this->end] = '\0';
		}

		inline void trim()
		{
			this->left_trim();
			this->right_trim();
		}

		void operator+=(c_str rhs)
		{
			msize n = 0;
			msize max_len = this->capacity() - 1;

			while (rhs[n] != '\0') {
				this->buf[this->end + n] = rhs[n];

				if (this->end + n == max_len) {
					this->buf.resize(max_len + 2*max_len);

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
		msize end;
		msize begin;

		// NOTE: See the note on the private copy-constructor of vector.
		inline string(string &other): buf(other.buf.move()), end(other.end), begin(other.begin)
		{
		}
	};

	#undef DEFAULT_STRING_LENGTH
#endif
