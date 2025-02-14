#if !defined(STRUCT_HEADER)
	#define STRUCT_HEADER
	#include "essentials.h"

	#if !defined(MAX_STRUCT_BLOCK_COUNT)
		#define MAX_STRUCT_BLOCK_COUNT 16
	#endif

	class Struct {
		public:
		inline Struct(): buf(0), block{0}
		{
		}

		Struct(Struct &&other): buf(other.buf.move()), block{other.block.count}
		{
			for (mut<usize> n = 0; n < other.block.count; ++n) {
				this->block.size[n] = other.block.size[n];
				this->block.length[n] = other.block.length[n];
				this->block.offset[n] = other.block.offset[n];
			}

			other.block.count = 0;
		}

		inline usize size() const
		{
			return this->buf.length();
		}

		inline usize member_count() const
		{
			return this->block.count;
		}

		inline usize member_size(usize n) const
		{
			return this->block.size[n];
		}

		inline usize member_length(usize n) const
		{
			return this->block.length[n];
		}

		template<typename T>
		inline void push_member(usize count = 1)
		{
			if constexpr(is_pointer<T>()) {
				this->setup_next_entry(sizeof(Target<T>), count);
			} else {
				this->setup_next_entry(sizeof(T), count);
			}
		}

		template<typename T, typename TARGET = typename std::enable_if<is_pointer<T>() == true, Target<T>>::type>
		mut<T> dereference(usize n)
		{
			if (sizeof(TARGET) != this->block.size[n]) {
				print::error(WHERE, "Type size mismatch when dereferencing member ", n, " as ", type_name<TARGET>(), '*');
			}

			mut<byte> *raw = this->member_ptr(n);

			return reinterpret_cast<mut<T>>(raw);
		}

		template<typename T, typename DUMMY = typename std::enable_if<is_pointer<T>() == false>::type>
		mut<T>& dereference(usize n)
		{
			if (sizeof(T) != this->block.size[n]) {
				print::error(WHERE, "Type size mismatch when dereferencing member ", n, " as ", type_name<T>());
			}

			mut<byte> *raw = this->member_ptr(n);

			return *reinterpret_cast<mut<T>*>(raw);
		}

		template<typename T>
		Vec<T> dereference_as_vec(usize n)
		{
			mut<T> *ptr = nullptr;

			if constexpr(is_pointer<T>()) {
				ptr = this->dereference<T>(n);
			} else {
				mut<T> &ref = this->dereference<T>(n);
				ptr = &ref;
			}

			// NOTE: Here, the vector must necessarily be set as a view and cannot
			// free the data when dropped. It is also needed to be fixed so that it
			// is not allowed to resize, since the Struct member size is fixed and
			// allocated contiguously in memory. The Struct object must outlive that
			// of the Vec<T> itself, otherwise it will be referencing garbage data.
			return Vec<T>(this->block.length[n], ptr);
		}

		template<typename T>
		inline Mat<T> dereference_as_mat(usize n, usize max_row, usize max_col)
		{
			Vec<T> raw = this->dereference_as_vec<T>(n);

			return Mat<T>(max_row, max_col, raw);
		}

		inline mut<byte>& operator[](usize n) const
		{
			return this->buf[n];
		}

		private:
		struct Block {
			mut<usize> count;
			mut<usize> size[MAX_STRUCT_BLOCK_COUNT];
			mut<usize> length[MAX_STRUCT_BLOCK_COUNT];
			mut<usize> offset[MAX_STRUCT_BLOCK_COUNT];
		};

		Vec<byte> buf;
		Block block;

		inline void append(usize next_chunk)
		{
			usize new_len = this->size() + next_chunk;

			this->buf.resize(new_len);
		}

		void setup_next_entry(usize size, usize count)
		{
			#pragma omp critical
			{
				usize n = this->block.count;

				if (n == MAX_STRUCT_BLOCK_COUNT) {
					print::error(WHERE, "Limit of ", MAX_STRUCT_BLOCK_COUNT, " members reached");
				}

				this->block.offset[n] = this->buf.length();

				this->block.length[n] = count;

				this->block.size[n] = size;

				this->append(size*count);

				this->block.count += 1;
			}
		}

		inline mut<byte>* member_ptr(usize n)
		{
			return &this->buf[this->block.offset[n]];
		}
	};

	#undef MAX_STRUCT_BLOCK_COUNT
#endif
