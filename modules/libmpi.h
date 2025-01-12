#if !defined(LIBMPI_HEADER)
	#define LIBMPI_HEADER
	#include "essentials.h"
	#include "struct.h"
	#include "input.h"
	#include "nist.h"
	#include <optional>

	namespace mpi {
		static constexpr u32 MASTER_PROCESS_RANK = 0u;

		bool is_used();

		bool using_petsc();

		bool using_slepc();

		void about();

		class Frontend {
			public:
			Frontend(mut<s32> *argc, char **argv[]);

			inline u32 world_size() const
			{
				return as_u32(this->comm_size);
			}

			inline u32 rank() const
			{
				return as_u32(this->my_rank);
			}

			inline usize task_count() const
			{
				// NOTE: The number of tasks for the current process.
				return this->total_tasks/this->world_size();
			}

			inline usize first_local_task() const
			{
				// NOTE: The first task index for the current process.
				return this->rank()*this->task_count();
			}

			inline usize last_local_task() const
			{
				// NOTE: The last task index for the current process.
				return this->first_local_task() + this->task_count() - 1u;
			}

			inline usize last_global_task() const
			{
				usize last_rank = this->world_size() - 1u;

				// NOTE: The last task index for the last process.
				return last_rank*this->task_count() + this->task_count() - 1u;
			}

			std::optional<usize> extra_task()
			{
				// NOTE: An additional task index for the current process.
				usize index = this->last_global_task() + this->rank() + 1u;

				if (index < this->total_tasks) {
					return index;
				} else {
					return {};
				}
			}

			inline void set_tasks(usize count)
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

			void send(u32 rank, u32 count, const nist::Isotope data[]) const;

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

			void send(u32 rank, const nist::Isotope data) const;

			void send(u32 rank, const Vec<u8> &data) const;

			void send(u32 rank, const Vec<u16> &data) const;

			void send(u32 rank, const Vec<u32> &data) const;

			void send(u32 rank, const Vec<u64> &data) const;

			void send(u32 rank, const Vec<s8> &data) const;

			void send(u32 rank, const Vec<s16> &data) const;

			void send(u32 rank, const Vec<s32> &data) const;

			void send(u32 rank, const Vec<s64> &data) const;

			void send(u32 rank, const Vec<char> &data) const;

			void send(u32 rank, const Vec<f32> &data) const;

			void send(u32 rank, const Vec<f64> &data) const;

			void send(u32 rank, const Vec<f128> &data) const;

			void send(u32 rank, const Vec<nist::Isotope> &data) const;

			void send(u32 rank, const Mat<u8> &data) const;

			void send(u32 rank, const Mat<u16> &data) const;

			void send(u32 rank, const Mat<u32> &data) const;

			void send(u32 rank, const Mat<u64> &data) const;

			void send(u32 rank, const Mat<s8> &data) const;

			void send(u32 rank, const Mat<s16> &data) const;

			void send(u32 rank, const Mat<s32> &data) const;

			void send(u32 rank, const Mat<s64> &data) const;

			void send(u32 rank, const Mat<char> &data) const;

			void send(u32 rank, const Mat<f32> &data) const;

			void send(u32 rank, const Mat<f64> &data) const;

			void send(u32 rank, const Mat<f128> &data) const;

			void send(u32 rank, const Mat<nist::Isotope> &data) const;

			void send(u32 rank, const String &data) const;

			void send(u32 rank, const Struct &data) const;

			void send(u32 rank, const Range<u8> &data) const;

			void send(u32 rank, const Range<u16> &data) const;

			void send(u32 rank, const Range<u32> &data) const;

			void send(u32 rank, const Range<u64> &data) const;

			void send(u32 rank, const Range<s8> &data) const;

			void send(u32 rank, const Range<s16> &data) const;

			void send(u32 rank, const Range<s32> &data) const;

			void send(u32 rank, const Range<s64> &data) const;

			void send(u32 rank, const Range<char> &data) const;

			void send(u32 rank, const Range<f32> &data) const;

			void send(u32 rank, const Range<f64> &data) const;

			void send(u32 rank, const Range<f128> &data) const;

			template<u8 PAD, usize LEN>
			void send(u32 rank, const print::Fmt<PAD, LEN> &data) const
			{
				this->send(rank, as_u32(data.len), &data.buf[0]);
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

			u32 receive(u32 rank, u32 count, nist::Isotope data[]) const;

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

			void receive(u32 rank, nist::Isotope &data) const;

			u32 receive(u32 rank, Vec<u8> &data) const;

			u32 receive(u32 rank, Vec<u16> &data) const;

			u32 receive(u32 rank, Vec<u32> &data) const;

			u32 receive(u32 rank, Vec<u64> &data) const;

			u32 receive(u32 rank, Vec<s8> &data) const;

			u32 receive(u32 rank, Vec<s16> &data) const;

			u32 receive(u32 rank, Vec<s32> &data) const;

			u32 receive(u32 rank, Vec<s64> &data) const;

			u32 receive(u32 rank, Vec<char> &data) const;

			u32 receive(u32 rank, Vec<f32> &data) const;

			u32 receive(u32 rank, Vec<f64> &data) const;

			u32 receive(u32 rank, Vec<f128> &data) const;

			u32 receive(u32 rank, Vec<nist::Isotope> &data) const;

			void receive(u32 rank, String &data) const;

			void receive(u32 rank, Struct &data) const;

			void receive(u32 rank, Range<u8> &data) const;

			void receive(u32 rank, Range<u16> &data) const;

			void receive(u32 rank, Range<u32> &data) const;

			void receive(u32 rank, Range<u64> &data) const;

			void receive(u32 rank, Range<s8> &data) const;

			void receive(u32 rank, Range<s16> &data) const;

			void receive(u32 rank, Range<s32> &data) const;

			void receive(u32 rank, Range<s64> &data) const;

			void receive(u32 rank, Range<char> &data) const;

			void receive(u32 rank, Range<f32> &data) const;

			void receive(u32 rank, Range<f64> &data) const;

			void receive(u32 rank, Range<f128> &data) const;

			template<u8 PAD, usize LEN>
			void receive(u32 rank, print::Fmt<PAD, LEN> &data) const
			{
				data.len = as_usize(this->receive(rank, LEN, &data.buf[0]));
			}

			template<typename T>
			void receive(u32 rank, Mat<T> &data) const
			{
				auto info = this->receive(rank, as_u32(data.rows()*data.cols()), &data[0]);
				assert(as_usize(info) == data.rows()*data.cols());
			}

			// NOTE: While the MPI broadcasts and gathers appear to be thread-safe,
			// they are used herein with the same group communicator and, therefore,
			// are also bound to OpenMP critical regions.

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

			void broadcast(u32 rank, u32 count, nist::Isotope data[]) const;

			void broadcast(u32 rank, Vec<u8> &data) const;

			void broadcast(u32 rank, Vec<u16> &data) const;

			void broadcast(u32 rank, Vec<u32> &data) const;

			void broadcast(u32 rank, Vec<u64> &data) const;

			void broadcast(u32 rank, Vec<s8> &data) const;

			void broadcast(u32 rank, Vec<s16> &data) const;

			void broadcast(u32 rank, Vec<s32> &data) const;

			void broadcast(u32 rank, Vec<s64> &data) const;

			void broadcast(u32 rank, Vec<char> &data) const;

			void broadcast(u32 rank, Vec<f32> &data) const;

			void broadcast(u32 rank, Vec<f64> &data) const;

			void broadcast(u32 rank, Vec<f128> &data) const;

			void broadcast(u32 rank, Vec<nist::Isotope> &data) const;

			void broadcast(u32 rank, Struct &data) const;

			void gather(u32 rank, u32 count, mut<u8> data[]) const;

			void gather(u32 rank, u32 count, mut<u16> data[]) const;

			void gather(u32 rank, u32 count, mut<u32> data[]) const;

			void gather(u32 rank, u32 count, mut<u64> data[]) const;

			void gather(u32 rank, u32 count, mut<s8> data[]) const;

			void gather(u32 rank, u32 count, mut<s16> data[]) const;

			void gather(u32 rank, u32 count, mut<s32> data[]) const;

			void gather(u32 rank, u32 count, mut<s64> data[]) const;

			void gather(u32 rank, u32 count, char data[]) const;

			void gather(u32 rank, u32 count, mut<f32> data[]) const;

			void gather(u32 rank, u32 count, mut<f64> data[]) const;

			void gather(u32 rank, u32 count, mut<f128> data[]) const;

			void wait() const;

			template<u8 PAD, usize LEN>
			void print_line(const print::Fmt<PAD, LEN> &content)
			{
				if (this->rank() == mpi::MASTER_PROCESS_RANK) {
					content.flush();

					for (mut<u32> rank = 1u; rank < this->world_size(); ++rank) {
						print::Fmt<PAD, LEN> new_content;

						this->receive(rank, new_content);

						if (new_content.len > 0) {
							new_content.flush();
						}
					}
				} else {
					this->send(mpi::MASTER_PROCESS_RANK, content);
				}
			}

			template<u8 PAD, usize LEN, typename T>
			void print_line(const print::Fmt<PAD, LEN> &prev, T last)
			{
				print::Fmt<PAD, LEN> end(last);
				this->print_line(prev + end);
			}

			template<u8 PAD, usize LEN, typename T, typename... Ts>
			void print_line(const print::Fmt<PAD, LEN> &prev, T first, Ts... remainder)
			{
				print::Fmt<PAD, LEN> next(first);
				this->print_line(prev + next, remainder...);
			}

			template<u8 PAD = 1, typename T, typename... Ts>
			void print_line(T first, Ts... remainder)
			{
				print::Fmt<PAD> start(first);
				this->print_line(start, remainder...);
			}

			// NOTE: Since the MPI runtime redirects the stdin to rank 0, wrappers
			// of the input::keyword() function are provided below to broadcast
			// standard inputs from rank 0 to others.

			template<typename T>
			T input_keyword(c_str key, T min, T max, T dummy)
			{
				T val = static_cast<T>(0);

				if (this->rank() == mpi::MASTER_PROCESS_RANK) {
					val = input::keyword(key, min, max, dummy);
				}

				this->broadcast(mpi::MASTER_PROCESS_RANK, 1, &val);

				return val;
			}

			String input_keyword(c_str key, c_str dummy = "\0")
			{
				String val;

				if (this->rank() == mpi::MASTER_PROCESS_RANK) {
					val += input::keyword(key, dummy).as_cstr();
				}

				this->broadcast(mpi::MASTER_PROCESS_RANK, 1, &val.end);

				if ((this->rank() != mpi::MASTER_PROCESS_RANK) && (val.end > val.buf.length())) {
					val.buf.resize(val.end);
				}

				this->broadcast(mpi::MASTER_PROCESS_RANK, as_u32(val.end), &val.buf[0]);

				return val;
			}

			bool input_keyword(c_str key, bool dummy)
			{
				mut<s32> val = 0;

				if (this->rank() == mpi::MASTER_PROCESS_RANK) {
					val = input::keyword(key, dummy);
				}

				this->broadcast(mpi::MASTER_PROCESS_RANK, 1, &val);

				return as_bool(val);
			}

			nist::Isotope input_keyword(c_str key, nist::Isotope dummy)
			{
				mut<u16> val = static_cast<u16>(nist::Isotope::atom_unknown);

				if (this->rank() == mpi::MASTER_PROCESS_RANK) {
					val = static_cast<u16>(input::keyword(key, dummy));
				}

				this->broadcast(mpi::MASTER_PROCESS_RANK, 1, &val);

				return static_cast<nist::Isotope>(val);
			}

			~Frontend();

			private:
			// NOTE: Signed ints are used for rank and comm_size in order
			// to match the MPI backend implementations.
			mut<s32> my_rank;
			mut<s32> comm_size;
			mut<usize> total_tasks;
		};
	}
#endif
