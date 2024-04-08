#if !defined(VECTOR_HEADER)
	#define VECTOR_HEADER
	#include "print.h"

	template<typename T = mut<f64>>
	class vector {
		public:
		inline vector(): len(0), buf(nullptr)
		{
		}

		inline vector(usize count): len(0), buf(nullptr)
		{
			this->resize(count);
		}

		inline vector(vector<T> &&other): len(other.len), buf(other.release())
		{
		}

		inline usize length() const
		{
			return this->len;
		}

		inline usize size() const
		{
			return sizeof(T)*this->len;
		}

		inline void operator=(const vector<T> &rhs)
		{
			usize n_max = (this->len < rhs.len? this->len : rhs.len);

			for (msize n = 0; n < n_max; ++n)
				this->buf[n] = rhs.buf[n];
		}

		inline void operator=(const T &rhs)
		{
			for (msize n = 0; n < this->len; ++n)
				this->buf[n] = rhs;
		}

		inline void operator+=(const T &rhs)
		{
			for (msize n = 0; n < this->len; ++n)
				this->buf[n] += rhs;
		}

		inline void operator-=(const T &rhs)
		{
			for (msize n = 0; n < this->len; ++n)
				this->buf[n] -= rhs;
		}

		inline void operator*=(const T &rhs)
		{
			for (msize n = 0; n < this->len; ++n)
				this->buf[n] *= rhs;
		}

		inline void operator/=(const T &rhs)
		{
			for (msize n = 0; n < this->len; ++n)
				this->buf[n] /= rhs;
		}

		inline T& operator[](usize n) const
		{
			return this->buf[n];
		}

		inline vector<T> move()
		{
			return vector(*this);
		}

		void swap(vector<T> &other)
		{
			auto len = this->len;
			auto buf = this->buf;

			this->len = other.len;
			this->buf = other.buf;

			other.len = len;
			other.buf = buf;
		}

		T* release()
		{
			auto raw = this->buf;
			this->buf = nullptr;
			this->len = 0;
			return raw;
		}

		void resize(usize count)
		{
			this->len = count;
			auto new_buf = std::realloc(as_void(this->buf), sizeof(T)*this->len);

			if ((new_buf == nullptr) && (count > 0)) {
				print::error(WHERE, "Unable to reallocate ", count, " elements of ", sizeof(T), " bytes");
			}

			this->buf = static_cast<T*>(new_buf);
		}

		inline ~vector()
		{
			if (this->buf != nullptr) {
				std::free(as_void(this->buf));
			}
		}

		private:
		msize len;
		T *buf;

		// NOTE: A copy-constructor from raw parts and internal use only which behaves
		// as a move-constructor. If made public, the compiler will perform unintended
		// moves as we don't want to share the internal buf pointer.
		inline vector(vector<T> &other): len(other.len), buf(other.release())
		{
		}
	};

	using vec32 = vector<mut<f32>>;
	using vec64 = vector<mut<f64>>;
#endif
