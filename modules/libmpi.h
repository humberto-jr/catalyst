#if !defined(LIBMPI_HEADER)
	#define LIBMPI_HEADER
	#include "essentials.h"
	#include "input.h"
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

			void send(u32 rank, u8 data) const;

			void send(u32 rank, u16 data) const;

			void send(u32 rank, u32 data) const;

			void send(u32 rank, u64 data) const;

			void send(u32 rank, s8 data) const;

			void send(u32 rank, s16 data) const;

			void send(u32 rank, s32 data) const;

			void send(u32 rank, s64 data) const;

			void send(u32 rank, char data) const;

			void send(u32 rank, f32 data) const;

			void send(u32 rank, f64 data) const;

			void send(u32 rank, f128 data) const;

			void send(u32 rank, const vec<u8> &data) const;

			void send(u32 rank, const vec<u16> &data) const;

			void send(u32 rank, const vec<u32> &data) const;

			void send(u32 rank, const vec<u64> &data) const;

			void send(u32 rank, const vec<s8> &data) const;

			void send(u32 rank, const vec<s16> &data) const;

			void send(u32 rank, const vec<s32> &data) const;

			void send(u32 rank, const vec<s64> &data) const;

			void send(u32 rank, const vec<char> &data) const;

			void send(u32 rank, const vec<f32> &data) const;

			void send(u32 rank, const vec<f64> &data) const;

			void send(u32 rank, const vec<f128> &data) const;

			void send(u32 rank, const string &data) const;

			template<u8 PAD, usize LEN>
			void send(u32 rank, const print::fmt<PAD, LEN> &data) const
			{
				this->send(rank, as_u32(data.len), &data.buf[0]);
			}

			template<typename T>
			void send(u32 rank, const mat<T> &data) const
			{
				this->send(rank, as_u32(data.rows()*data.cols()), &data[0]);
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

			void receive(u32 rank, mut<u8> &data) const;

			void receive(u32 rank, mut<u16> &data) const;

			void receive(u32 rank, mut<u32> &data) const;

			void receive(u32 rank, mut<u64> &data) const;

			void receive(u32 rank, mut<s8> &data) const;

			void receive(u32 rank, mut<s16> &data) const;

			void receive(u32 rank, mut<s32> &data) const;

			void receive(u32 rank, mut<s64> &data) const;

			void receive(u32 rank, char &data) const;

			void receive(u32 rank, mut<f32> &data) const;

			void receive(u32 rank, mut<f64> &data) const;

			void receive(u32 rank, mut<f128> &data) const;

			u32 receive(u32 rank, vec<u8> &data) const;

			u32 receive(u32 rank, vec<u16> &data) const;

			u32 receive(u32 rank, vec<u32> &data) const;

			u32 receive(u32 rank, vec<u64> &data) const;

			u32 receive(u32 rank, vec<s8> &data) const;

			u32 receive(u32 rank, vec<s16> &data) const;

			u32 receive(u32 rank, vec<s32> &data) const;

			u32 receive(u32 rank, vec<s64> &data) const;

			u32 receive(u32 rank, vec<char> &data) const;

			u32 receive(u32 rank, vec<f32> &data) const;

			u32 receive(u32 rank, vec<f64> &data) const;

			u32 receive(u32 rank, vec<f128> &data) const;

			void receive(u32 rank, string &data) const;

			template<u8 PAD, usize LEN>
			void receive(u32 rank, print::fmt<PAD, LEN> &data) const
			{
				data.len = as_usize(this->receive(rank, LEN, &data.buf[0]));
			}

			template<typename T>
			void receive(u32 rank, mat<T> &data) const
			{
				auto info = this->receive(rank, as_u32(data.rows()*data.cols()), &data[0]);
				assert(as_usize(info) == data.rows()*data.cols());
			}

			// NOTE: While the MPI broadcasts appear to be thread-safe, they are
			// used herein with the same group communicator and, therefore, are
			// also bound to OpenMP critical regions.

			void broadcast(u32 rank, u32 count, mut<u8> data[]) const;

			void broadcast(u32 rank, u32 count, mut<u16> data[]) const;

			void broadcast(u32 rank, u32 count, mut<u32> data[]) const;

			void broadcast(u32 rank, u32 count, mut<u64> data[]) const;

			void broadcast(u32 rank, u32 count, mut<s8> data[]) const;

			void broadcast(u32 rank, u32 count, mut<s16> data[]) const;

			void broadcast(u32 rank, u32 count, mut<s32> data[]) const;

			void broadcast(u32 rank, u32 count, mut<s64> data[]) const;

			void broadcast(u32 rank, u32 count, char data[]) const;

			void broadcast(u32 rank, u32 count, mut<f32> data[]) const;

			void broadcast(u32 rank, u32 count, mut<f64> data[]) const;

			void broadcast(u32 rank, u32 count, mut<f128> data[]) const;

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

						print::fmt<PAD, LEN> new_content;

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

			// NOTE: Since the MPI runtime redirects the stdin to rank 0, wrappers
			// of the input::keyword() function are provided below to broadcast
			// standard inputs from rank 0 to others.

			template<typename T>
			T input_keyword(c_str key, T min, T max, T dummy)
			{
				T val = static_cast<T>(0);

				if (this->rank() == MASTER_PROCESS_RANK) {
					val = input::keyword(key, min, max, dummy);
				}

				this->broadcast(MASTER_PROCESS_RANK, 1, &val);

				return val;
			}

			string input_keyword(c_str key, c_str dummy = "\0")
			{
				string val;

				if (this->rank() == MASTER_PROCESS_RANK) {
					val += input::keyword(key, dummy).as_cstr();
				}

				this->broadcast(MASTER_PROCESS_RANK, 1, &val.end);

				if ((this->rank() != MASTER_PROCESS_RANK) && (val.end > val.buf.length())) {
					val.buf.resize(val.end);
				}

				this->broadcast(MASTER_PROCESS_RANK, as_u32(val.end), &val.buf[0]);

				return val;
			}

			bool input_keyword(c_str key, bool dummy)
			{
				mut<s32> val = 0;

				if (this->rank() == MASTER_PROCESS_RANK) {
					val = input::keyword(key, dummy);
				}

				this->broadcast(MASTER_PROCESS_RANK, 1, &val);

				return as_bool(val);
			}

			nist::isotope input_keyword(c_str key, nist::isotope dummy)
			{
				mut<u16> val = static_cast<u16>(nist::isotope::atom_unknown);

				if (this->rank() == MASTER_PROCESS_RANK) {
					val = static_cast<u16>(input::keyword(key, dummy));
				}

				this->broadcast(MASTER_PROCESS_RANK, 1, &val);

				return static_cast<nist::isotope>(val);
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
