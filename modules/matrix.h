#if !defined(MATRIX_HEADER)
	#define MATRIX_HEADER
	#include "types.h"
	#include "vector.h"

	namespace lapack {
		// NOTE: Forward declaration to avoid include liblapack.h here.
		class frontend;
	}

	template<typename T = mut<f64>>
	class matrix {
		public:
		inline matrix(usize max_row, usize max_col): max_col(max_col), buf(vector<T>(max_row*max_col))
		{
		}

		inline matrix(matrix &&other): max_col(other.max_col), buf(other.buf.move())
		{
			other.max_col = 0;
		}

		inline bool is_valid() const
		{
			return (this->buf.length() > 0);
		}

		inline usize rows() const
		{
			return this->buf.length()/this->max_col;
		}

		inline usize cols() const
		{
			return this->max_col;
		}

		inline usize size() const
		{
			return this->buf.size();
		}

		inline void operator=(const T rhs)
		{
			this->buf = rhs;
		}

		inline void operator=(const matrix<T> &rhs)
		{
			this->buf = rhs.buf;
		}

		inline T& operator()(usize n, usize m) const
		{
			// NOTE: Row-major layout.
			return this->buf[n*this->max_col + m];
		}

		inline T& operator[](usize n) const
		{
			return this->buf[n];
		}

		inline matrix<T> move()
		{
			return matrix(*this);
		}

		void swap(matrix<T> &other)
		{
			auto max_col = this->max_col;

			this->max_col = other.max_col;
			this->buf.swap(other.buf);

			other.max_col = max_col;
		}

		class view {
			public:
			inline usize rows() const
			{
				return (this->row_max - this->row_min + 1);
			}

			inline usize cols() const
			{
				return (this->col_max - this->col_min + 1);
			}

			inline usize size() const
			{
				return sizeof(T)*this->rows()*this->cols();
			}

			void operator=(const T rhs)
			{
				for (mut<usize> n = 0; n < this->rows(); ++n)
					for (mut<usize> m = 0; m < this->cols(); ++m)
						this->operator()(n, m) = rhs;
			}

			T& operator()(usize n, usize m) const
			{
				usize block_n = this->row_min + n;
				assert(block_n < this->row_max + 1);

				usize block_m = this->col_min + m;
				assert(block_m < this->col_max + 1);

				return this->owner(block_n, block_m);
			}

			private:
			usize row_min;
			usize row_max;
			usize col_min;
			usize col_max;
			matrix<T> &owner;

			view(usize row_start, usize row_end, usize col_start, usize col_end, matrix<T> &owner):
				row_min(row_start), row_max(row_end), col_min(col_start), col_max(col_end), owner(owner)
			{
				assert(row_end >= row_start);
				assert(col_end >= col_start);
				assert(owner.is_valid());
			}

			// NOTE: We bind the constructor of views to a method of the parent matrix
			// in order to enforce that the parent class outlives the child, as the
			// destructors are called in a LIFO order. Still, care should be taken
			// whenever handling complex lifetimes, like pointers to views and/or
			// static views. Avoid those, if possible.
			friend inline view matrix<T>::block_view(usize, usize, usize, usize);
		};

		inline view block_view(usize row_start, usize row_end, usize col_start, usize col_end)
		{
			return view(row_start, row_end, col_start, col_end, *this);
		}

		inline view row_view(usize n)
		{
			return this->block_view(n, n, 0, this->cols() - 1);
		}

		inline view col_view(usize m)
		{
			return this->block_view(0, this->rows() - 1, m, m);
		}

		private:
		friend class lapack::frontend;

		mut<usize> max_col;
		vector<T> buf;

		// NOTE: See the note on the private copy-constructor of vector.
		inline matrix(matrix &other): max_col(other.max_col), buf(other.buf.move())
		{
		}
	};

	using mat32 = matrix<mut<f32>>;
	using mat64 = matrix<mut<f64>>;
#endif
