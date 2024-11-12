#if !defined(VECTOR_HEADER)
	#define VECTOR_HEADER
	#include "print.h"
	#include <initializer_list>

	template<typename T = f64>
	class Vector {
		public:
		using type = T;

		inline Vector(): len(0), buf(nullptr), state(0)
		{
		}

		inline Vector(usize count): len(0), buf(nullptr), state(0)
		{
			this->resize(count);
		}

		inline Vector(usize count, mut<T> *raw): len(count), buf(raw), state(IS_VIEW | IS_FIXED)
		{
			assert(this->buf != nullptr);
		}

		inline Vector(Vector<T> &&other): len(other.len), buf(other.release()), state(other.state)
		{
		}

		inline Vector(const std::initializer_list<T> &rhs): len(rhs.size()), buf(nullptr), state(0)
		{
			 this->resize(rhs.size());
			*this = rhs;
		}

		inline Vector(Vector<T> &other): len(other.len), buf(other.buf), state(other.state | IS_VIEW)
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

		inline bool is_view() const
		{
			return ((this->state & IS_VIEW) == IS_VIEW);
		}

		inline bool is_fixed() const
		{
			return ((this->state & IS_FIXED) == IS_FIXED);
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
			return std::move(*this);
		}

		void swap(Vector<T> &other)
		{
			auto len = this->len;
			auto buf = this->buf;
			auto state = this->state;

			this->len = other.len;
			this->buf = other.buf;
			this->state = other.state;

			other.len = len;
			other.buf = buf;
			other.state = state;
		}

		mut<T>* release()
		{
			// NOTE: We must keep its current state because it is used in the
			// move constructor after the release.
			auto raw = this->buf;
			this->buf = nullptr;
			this->len = 0;
			return raw;
		}

		void resize(usize count)
		{
			if (count == 0) {
				return;
			}

			if (this->is_fixed()) {
				print::error(WHERE, "Unable to resize a fixed vector");
			}

			auto new_buf = std::realloc(as_void(this->buf), sizeof(T)*count);

			if (new_buf == nullptr) {
				print::error(WHERE, "Unable to reallocate ", count, " elements of ", sizeof(T), " bytes");
			} else {
				this->buf = static_cast<mut<T>*>(new_buf);
			}

			if (count > this->len) {
				usize chunk = count - this->len;
				std::memset(as_void(this->buf + this->len), 0, sizeof(T)*chunk);
			}

			this->len = count;
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
			if ((this->buf != nullptr) && (this->is_view() == false)) {
				std::free(as_void(this->buf));
			}
		}

		private:
		mut<usize> len;
		mut<T> *buf;
		mut<u8> state;

		enum State {
			IS_VIEW  = (1u << 0),
			IS_FIXED = (1u << 1)
		};
	};

	template<typename T = f64>
	using Vec = Vector<T>;
#endif
