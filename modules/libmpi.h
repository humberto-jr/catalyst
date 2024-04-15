#if !defined(LIBMPI_HEADER)
	#define LIBMPI_HEADER
	#include "essentials.h"
	#include <optional>

	namespace mpi {
		static constexpr u32 MASTER_PROCESS_RANK = 0;

		bool is_used();

		bool using_petsc();

		bool using_slepc();

		void about();

		class frontend {
			public:
			frontend(mut<s32> *argc, char **argv[]);

			inline u32 world_size() const
			{
				return as_u32(this->comm_size);
			}

			inline u32 rank() const
			{
				return as_u32(this->my_rank);
			}

			inline u32 task_count() const
			{
				// NOTE: The number of tasks for the current process.
				return this->total_tasks/this->world_size();
			}

			inline u32 first_local_task() const
			{
				// NOTE: The first task index for the current process.
				return this->rank()*this->task_count();
			}

			inline u32 last_local_task() const
			{
				// NOTE: The last task index for the current process.
				return this->first_local_task() + this->task_count() - 1;
			}

			inline u32 last_global_task() const
			{
				u32 last_rank = this->world_size() - 1;

				// NOTE: The last task index for the last process.
				return last_rank*this->task_count() + this->task_count() - 1;
			}

			std::optional<u32> extra_task()
			{
				// NOTE: An additional task index for the current process.
				u32 index = this->last_global_task() + this->rank() + 1;

				if (index < this->total_tasks) {
					return index;
				} else {
					return {};
				}
			}

			inline void set_tasks(u32 count)
			{
				assert(count > 0);
				this->total_tasks = count;
			}

			// NOTE: MPI specify the message length in terms of number of elements,
			// not number of bytes. The former is machine independent and closer to
			// the application level. Thus, u32 is used below instead of usize.

			void send(u32 rank, u32 count, u8 data[]) const;

			void send(u32 rank, u32 count, u16 data[]) const;

			void send(u32 rank, u32 count, u32 data[]) const;

			void send(u32 rank, u32 count, u64 data[]) const;

			void send(u32 rank, u32 count, s8 data[]) const;

			void send(u32 rank, u32 count, s16 data[]) const;

			void send(u32 rank, u32 count, s32 data[]) const;

			void send(u32 rank, u32 count, s64 data[]) const;

			void send(u32 rank, u32 count, const char data[]) const;

			void send(u32 rank, u32 count, f32 data[]) const;

			void send(u32 rank, u32 count, f64 data[]) const;

			void send(u32 rank, u32 count, f128 data[]) const;

			template<u8 PAD, usize LEN>
			void send(u32 rank, const print::fmt<PAD, LEN> &data) const
			{
				send(rank, as_u32(data.len), &data.buf[0]);
			}

			template<typename T>
			void send(u32 rank, const vector<T> &data) const
			{
				send(rank, as_u32(data.length()), &data[0]);
			}

			template<typename T>
			void send(u32 rank, const matrix<T> &data) const
			{
				send(rank, as_u32(data.rows()*data.cols()), &data[0]);
			}

			u32 receive(u32 rank, u32 count, mut<u8> data[]) const;

			u32 receive(u32 rank, u32 count, mut<u16> data[]) const;

			u32 receive(u32 rank, u32 count, mut<u32> data[]) const;

			u32 receive(u32 rank, u32 count, mut<u64> data[]) const;

			u32 receive(u32 rank, u32 count, mut<s8> data[]) const;

			u32 receive(u32 rank, u32 count, mut<s16> data[]) const;

			u32 receive(u32 rank, u32 count, mut<s32> data[]) const;

			u32 receive(u32 rank, u32 count, mut<s64> data[]) const;

			u32 receive(u32 rank, u32 count, char data[]) const;

			u32 receive(u32 rank, u32 count, mut<f32> data[]) const;

			u32 receive(u32 rank, u32 count, mut<f64> data[]) const;

			u32 receive(u32 rank, u32 count, mut<f128> data[]) const;

			template<u8 PAD, usize LEN>
			void receive(u32 rank, print::fmt<PAD, LEN> &data) const
			{
				data.len = as_usize(receive(rank, LEN, &data.buf[0]));
			}

			template<typename T>
			void receive(u32 rank, vector<T> &data) const
			{
				auto info = receive(rank, as_u32(data.length()), &data[0]);
				assert(as_usize(info) <= data.length());
			}

			template<typename T>
			void receive(u32 rank, matrix<T> &data) const
			{
				auto info = receive(rank, as_u32(data.rows()*data.cols()), &data[0]);
				assert(as_usize(info) == data.rows()*data.cols());
			}

			void wait() const;

			template<u8 PAD, usize LEN>
			void print_line(const print::fmt<PAD, LEN> &content)
			{
				if (this->rank() == MASTER_PROCESS_RANK) {
					content.flush();

					for (mut<u32> rank = 0; rank < this->world_size(); ++rank) {
						if (rank == MASTER_PROCESS_RANK) {
							continue;
						}

						print::fmt<LEN> new_content;

						this->receive(rank, new_content);

						if (new_content.len > 0) {
							new_content.flush();
						}
					}
				} else {
					this->send(MASTER_PROCESS_RANK, content);
				}
			}

			template<u8 PAD, usize LEN, typename T>
			void print_line(const print::fmt<PAD, LEN> &prev, T last)
			{
				print::fmt<PAD, LEN> end(last);
				this->print_line(prev + end);
			}

			template<u8 PAD, usize LEN, typename T, typename... Ts>
			void print_line(const print::fmt<PAD, LEN> &prev, T first, Ts... remainder)
			{
				print::fmt<PAD, LEN> next(first);
				this->print_line(prev + next, remainder...);
			}

			template<u8 PAD = 1, typename T, typename... Ts>
			void print_line(T first, Ts... remainder)
			{
				print::fmt<PAD> start(first);
				this->print_line(start, remainder...);
			}

			~frontend();

			private:
			// NOTE: Signed ints are used for rank and comm_size in order
			// to match the MPI backend implementations.
			mut<s32> my_rank;
			mut<s32> comm_size;
			mut<u32> total_tasks;
		};
	}
#endif
