#if !defined(VECTOR_HEADER)
	#define VECTOR_HEADER
	#include "print.h"
	#include <memory>
	#include <initializer_list>

	template<typename T = f64>
	class Vector {
		public:
		inline Vector(): len(0), buf(nullptr)
		{
		}

		inline Vector(usize count): len(0), buf(nullptr)
		{
			this->resize(count);
		}

		inline Vector(Vector<T> &&other): len(other.len), buf(other.release())
		{
		}

		inline Vector(const std::initializer_list<T> &rhs): len(rhs.size()), buf(nullptr)
		{
			 this->resize(rhs.size());
			*this = rhs;
		}

		inline Vector(usize count, std::unique_ptr<T> &raw): len(count), buf(raw.release())
		{
			assert(this->buf != nullptr);
		}

		inline usize length() const
		{
			return this->len;
		}

		inline usize size() const
		{
			return sizeof(T)*this->len;
		}

		void operator=(const std::initializer_list<T> &rhs)
		{
			usize n_max = (this->len < rhs.size()? this->len : rhs.size());

			auto val = rhs.begin();

			for (mut<usize> n = 0; n < n_max; ++n) {
				this->buf[n] = *val;
				++val;
			}
		}

		inline void operator=(const Vector<T> &rhs)
		{
			usize n_max = (this->len < rhs.len? this->len : rhs.len);

			for (mut<usize> n = 0; n < n_max; ++n)
				this->buf[n] = rhs.buf[n];
		}

		inline void operator=(const T &rhs)
		{
			for (mut<usize> n = 0; n < this->len; ++n)
				this->buf[n] = rhs;
		}

		inline void operator+=(const T &rhs)
		{
			for (mut<usize> n = 0; n < this->len; ++n)
				this->buf[n] += rhs;
		}

		inline void operator-=(const T &rhs)
		{
			for (mut<usize> n = 0; n < this->len; ++n)
				this->buf[n] -= rhs;
		}

		inline void operator*=(const T &rhs)
		{
			for (mut<usize> n = 0; n < this->len; ++n)
				this->buf[n] *= rhs;
		}

		inline void operator/=(const T &rhs)
		{
			for (mut<usize> n = 0; n < this->len; ++n)
				this->buf[n] /= rhs;
		}

		inline mut<T>& operator[](usize n) const
		{
			return this->buf[n];
		}

		inline Vector<T> move()
		{
			return Vector(*this);
		}

		void swap(Vector<T> &other)
		{
			auto len = this->len;
			auto buf = this->buf;

			this->len = other.len;
			this->buf = other.buf;

			other.len = len;
			other.buf = buf;
		}

		mut<T>* release()
		{
			auto raw = this->buf;
			this->buf = nullptr;
			this->len = 0;
			return raw;
		}

		void resize(usize count)
		{
			auto new_buf = std::realloc(as_void(this->buf), sizeof(T)*count);

			if ((new_buf == nullptr) && (count > 0)) {
				print::error(WHERE, "Unable to reallocate ", count, " elements of ", sizeof(T), " bytes");
			}

			if (this->len == 0) {
				std::memset(new_buf, 0, sizeof(T)*count);
			}

			this->len = count;
			this->buf = static_cast<mut<T>*>(new_buf);
		}

		struct IndexedEntry {
			mut<T> &value;
			usize index;
		};

		class Iterator {
			public:
			inline Iterator(const Vector<T> &owner): index(0u), buf(owner.buf)
			{
			}

			inline bool operator!=(usize max_len) const
			{
				return (this->index < max_len);
			}

			inline Vector<T>::IndexedEntry operator*() const
			{
				return {this->buf[this->index], this->index};
			}

			inline void operator++()
			{
				this->index += 1u;
			}

			private:
			mut<usize> index;
			mut<T> *buf;
		};

		inline Vector<T>::Iterator begin() const
		{
			return Vector<T>::Iterator(*this);
		}

		inline usize end() const
		{
			return this->len;
		}

		inline ~Vector()
		{
			if (this->buf != nullptr) {
				std::free(as_void(this->buf));
			}
		}

		private:
		mut<usize> len;
		mut<T> *buf;

		// NOTE: A copy-constructor from raw parts and internal use only which behaves
		// as a move-constructor. If made public, the compiler will perform unintended
		// moves as we don't want to share the internal buf pointer.
		inline Vector(Vector<T> &other): len(other.len), buf(other.release())
		{
		}
	};

	template<typename T = f64>
	using Vec = Vector<T>;
#endif
