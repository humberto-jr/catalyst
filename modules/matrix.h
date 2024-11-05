#if !defined(MATRIX_HEADER)
	#define MATRIX_HEADER
	#include "types.h"
	#include "vector.h"

	template<typename T = f64>
	class Matrix {
		public:
		using type = T;

		inline Matrix(usize max_row, usize max_col): max_col(max_col), buf(max_row*max_col)
		{
		}

		inline Matrix(Matrix &&other): max_col(other.max_col), buf(other.buf.move())
		{
			other.max_col = 0;
		}

		inline Matrix(usize max_row, usize max_col, Vec<T> &raw): max_col(max_col), buf(raw)
		{
			assert(this->length() == max_row*max_col);
		}

		inline usize length() const
		{
			return this->buf.length();
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

		inline void operator=(const T &rhs)
		{
			this->buf = rhs;
		}

		inline void operator=(const Matrix<T> &rhs)
		{
			this->buf = rhs.buf;
		}

		inline mut<T>& operator()(usize n, usize m) const
		{
			// NOTE: Row-major layout.
			return this->buf[n*this->max_col + m];
		}

		inline mut<T>& operator[](usize n) const
		{
			return this->buf[n];
		}

		inline Matrix<T> move()
		{
			return Matrix(*this);
		}

		void swap(Matrix<T> &other)
		{
			auto max_col = this->max_col;

			this->max_col = other.max_col;
			this->buf.swap(other.buf);

			other.max_col = max_col;
		}

		inline void resize(usize max_row, usize max_col)
		{
			this->max_col = max_col;
			this->buf.resize(max_row*max_col);
		}

		class View {
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

			void operator=(const T &rhs)
			{
				for (mut<usize> n = 0; n < this->rows(); ++n)
					for (mut<usize> m = 0; m < this->cols(); ++m)
						this->operator()(n, m) = rhs;
			}

			mut<T>& operator()(usize n, usize m) const
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
			Matrix<T> &owner;

			View(usize row_start, usize row_end, usize col_start, usize col_end, Matrix<T> &owner):
				row_min(row_start), row_max(row_end), col_min(col_start), col_max(col_end), owner(owner)
			{
				assert(row_end >= row_start);
				assert(col_end >= col_start);
				assert(owner.length() > 0);
			}

			// NOTE: We bind the constructor of View to a method of the parent Matrix
			// in order to enforce that the parent class outlives the child, as the
			// destructors are called in a LIFO order. Still, care should be taken
			// whenever handling complex lifetimes, like pointers to View and/or
			// static View. Avoid those, if possible.
			friend class Matrix<T>;
		};

		inline Matrix<T>::View block_view(usize row_start, usize row_end, usize col_start, usize col_end)
		{
			return Matrix<T>::View(row_start, row_end, col_start, col_end, *this);
		}

		inline Matrix<T>::View row_view(usize n)
		{
			return this->block_view(n, n, 0, this->cols() - 1);
		}

		inline Matrix<T>::View col_view(usize m)
		{
			return this->block_view(0, this->rows() - 1, m, m);
		}

		void row_copy(usize n, Vec<T> &row) const
		{
			usize count = this->cols();

			if (row.length() < count) {
				row.resize(count);
			}

			for (mut<usize> m = 0; m < count; ++m) {
				row[m] = (*this)(n, m);
			}
		}

		void col_copy(usize m, Vec<T> &col) const
		{
			usize count = this->rows();

			if (col.length() < count) {
				col.resize(count);
			}

			for (mut<usize> n = 0; n < count; ++n) {
				col[n] = (*this)(n, m);
			}
		}

		private:
		mut<usize> max_col;
		Vec<T> buf;

		inline Matrix(Matrix &other): max_col(other.max_col), buf(other.buf.move())
		{
		}
	};

	template<typename T = f64>
	using Mat = Matrix<T>;
#endif
