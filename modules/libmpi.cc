#include "libmpi.h"

#if defined(USE_MPI) && !defined(USE_PETSC)
	#include "mpi.h"
#endif

#if defined(USE_PETSC)
	#include <petscvec.h>
	#include <petscmat.h>

	#if defined(USE_SLEPC)
		#include "slepceps.h"
	#endif

	// NOTE: For use inside mpi::Frontend methods only.
	#define CHECK_PETSC_ERROR(name, code)                                                                \
	{                                                                                                    \
	  if ((code) != 0) {                                                                                 \
	    print::error(WHERE, "At rank ", this->rank(), ": ", name, "() failed with error code ", (code)); \
	  }                                                                                                  \
	}
#endif

// NOTE: For use inside mpi::Frontend methods only.
#define CHECK_MPI_ERROR(name, code)                                                                  \
{                                                                                                    \
  if ((code) != MPI_SUCCESS) {                                                                       \
    print::error(WHERE, "At rank ", this->rank(), ": ", (name), " failed with error code ", (code)); \
  }                                                                                                  \
}

#define CALL_SYNC_MPI_SEND(rank, count, buffer, datatype)                                      \
{                                                                                              \
  auto info = MPI_Send(&(count), 1, MPI_UINT32_T, (rank), MESSAGE_COUNT_TAG, MPI_COMM_WORLD);  \
                                                                                               \
  CHECK_MPI_ERROR("1st MPI_Send()", info)                                                      \
                                                                                               \
  info = MPI_Send(&buffer[0], (count), datatype, (rank), MESSAGE_CONTENT_TAG, MPI_COMM_WORLD); \
                                                                                               \
  CHECK_MPI_ERROR("2nd MPI_Send()", info)                                                      \
}

#define CALL_SYNC_MPI_RECEIVE(rank, recv_count, count, buffer, datatype)                                            \
{                                                                                                                   \
  auto info = MPI_Recv(&recv_count, 1, MPI_UINT32_T, (rank), MESSAGE_COUNT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE); \
                                                                                                                    \
  CHECK_MPI_ERROR("1st MPI_Recv()", info)                                                                           \
                                                                                                                    \
  if ((count) >= recv_count) {                                                                                      \
    info = MPI_Recv(&data[0], (count), datatype, (rank), MESSAGE_CONTENT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);   \
                                                                                                                    \
    CHECK_MPI_ERROR("2nd MPI_Recv()", info)                                                                         \
  }                                                                                                                 \
}

#define CALL_MPI_BROADCAST(rank, count, buffer, datatype)                     \
{                                                                             \
  auto info = MPI_Bcast(&data[0], (count), datatype, (rank), MPI_COMM_WORLD); \
                                                                              \
  CHECK_MPI_ERROR("MPI_Bcast()", info)                                        \
}

[[maybe_unused]]
static constexpr s32 MESSAGE_COUNT_TAG = 666;

[[maybe_unused]]
static constexpr s32 MESSAGE_CONTENT_TAG = 667;

//
// Public:
//

bool mpi::is_used()
{
	#if defined(USE_MPI)
		return true;
	#else
		return false;
	#endif
}

bool mpi::using_petsc()
{
	#if defined(USE_PETSC)
		return true;
	#else
		return false;
	#endif
}

bool mpi::using_slepc()
{
	#if defined(USE_PETSC) && defined(USE_SLEPC)
		return true;
	#else
		return false;
	#endif
}

void mpi::about()
{
	print::line("# Date = ", __DATE__);
	print::line("# File = ", __FILE__);
	print::line("# Using MPI = ", (is_used()? "yes" : "no"));
	print::line("# Using PETSc = ", (using_petsc()? "yes" : "no"));
	print::line("# Using SLEPc = ", (using_slepc()? "yes" : "no"));
}

mpi::Frontend::Frontend(mut<s32> *argc, char **argv[]):
	my_rank(0), comm_size(1), total_tasks(1)
{
	assert(*argc > -1);
	assert(argv != nullptr);

	#if defined(USE_MPI)
		#pragma omp master
		{
			auto info = 0;

			#if defined(USE_PETSC)
				info = PetscInitialize(&argc, &argv, nullptr, nullptr);
				CHECK_PETSC_ERROR("PetscInitialize()", info)

				#if defined(USE_SLEPC)
					info = SlepcInitialize(&argc, &argv, nullptr, nullptr);
					CHECK_PETSC_ERROR("SlepcInitialize()", info)
				#endif
			#else
				// NOTE: The process may be multi-threaded, and multiple threads may
				// make MPI calls, but only one at a time, i.e., MPI calls are not made
				// concurrently from two distinct threads (all MPI calls are serialized).
				// This module is responsible for reinforcing the correct usage, unless
				// PETSC and SLEPC are used, in which case the thread model is chosen by them.
				mut<s32> thread_level = 0;

				info = MPI_Init_thread(argc, argv, MPI_THREAD_SERIALIZED, &thread_level);
				CHECK_MPI_ERROR("MPI_Init_thread()", info)

				assert(thread_level == MPI_THREAD_SERIALIZED);
			#endif

			info = MPI_Comm_size(MPI_COMM_WORLD, &this->comm_size);
			CHECK_MPI_ERROR("MPI_Comm_size()", info)

			info = MPI_Comm_rank(MPI_COMM_WORLD, &this->my_rank);
			CHECK_MPI_ERROR("MPI_Comm_rank()", info)
		}
	#endif
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] u8 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_SEND(rank, count, data, MPI_UINT8_T)
	#endif
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] u16 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_SEND(rank, count, data, MPI_UINT16_T)
	#endif
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] u32 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_SEND(rank, count, data, MPI_UINT32_T)
	#endif
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] u64 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_SEND(rank, count, data, MPI_UINT64_T)
	#endif
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] s8 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_SEND(rank, count, data, MPI_INT8_T)
	#endif
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] s16 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_SEND(rank, count, data, MPI_INT16_T)
	#endif
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] s32 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_SEND(rank, count, data, MPI_INT32_T)
	#endif
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] s64 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_SEND(rank, count, data, MPI_INT64_T)
	#endif
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] const char data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_SEND(rank, count, data, MPI_CHAR)
	#endif
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] f32 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_SEND(rank, count, data, MPI_FLOAT)
	#endif
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] f64 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_SEND(rank, count, data, MPI_DOUBLE)
	#endif
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] f128 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_SEND(rank, count, data, MPI_LONG_DOUBLE)
	#endif
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u8 data) const
{
	this->send(rank, 1, &data);
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u16 data) const
{
	this->send(rank, 1, &data);
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 data) const
{
	this->send(rank, 1, &data);
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u64 data) const
{
	this->send(rank, 1, &data);
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] s8 data) const
{
	this->send(rank, 1, &data);
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] s16 data) const
{
	this->send(rank, 1, &data);
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] s32 data) const
{
	this->send(rank, 1, &data);
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] s64 data) const
{
	this->send(rank, 1, &data);
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] const char data) const
{
	this->send(rank, 1, &data);
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] f32 data) const
{
	this->send(rank, 1, &data);
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] f64 data) const
{
	this->send(rank, 1, &data);
}

void mpi::Frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] f128 data) const
{
	this->send(rank, 1, &data);
}

// NOTE: For use inside mpi::Frontend::send() methods only.
#define SEND_VECTOR_DATA(rank, data)         \
{                                            \
  usize len = data.length();                 \
  this->send((rank), 1, &len);               \
  this->send((rank), as_u32(len), &data[0]); \
}

void mpi::Frontend::send(u32 rank, const Vec<u8> &data) const
{
	SEND_VECTOR_DATA(rank, data)
}

void mpi::Frontend::send(u32 rank, const Vec<u16> &data) const
{
	SEND_VECTOR_DATA(rank, data)
}

void mpi::Frontend::send(u32 rank, const Vec<u32> &data) const
{
	SEND_VECTOR_DATA(rank, data)
}

void mpi::Frontend::send(u32 rank, const Vec<u64> &data) const
{
	SEND_VECTOR_DATA(rank, data)
}

void mpi::Frontend::send(u32 rank, const Vec<s8> &data) const
{
	SEND_VECTOR_DATA(rank, data)
}

void mpi::Frontend::send(u32 rank, const Vec<s16> &data) const
{
	SEND_VECTOR_DATA(rank, data)
}

void mpi::Frontend::send(u32 rank, const Vec<s32> &data) const
{
	SEND_VECTOR_DATA(rank, data)
}

void mpi::Frontend::send(u32 rank, const Vec<s64> &data) const
{
	SEND_VECTOR_DATA(rank, data)
}

void mpi::Frontend::send(u32 rank, const Vec<char> &data) const
{
	SEND_VECTOR_DATA(rank, data)
}

void mpi::Frontend::send(u32 rank, const Vec<f32> &data) const
{
	SEND_VECTOR_DATA(rank, data)
}

void mpi::Frontend::send(u32 rank, const Vec<f64> &data) const
{
	SEND_VECTOR_DATA(rank, data)
}

void mpi::Frontend::send(u32 rank, const Vec<f128> &data) const
{
	SEND_VECTOR_DATA(rank, data)
}

void mpi::Frontend::send(u32 rank, const String &data) const
{
	// NOTE: The string and the null-terminator character are sent.
	auto len = data.length();
	this->send(rank, 1, &len);
	this->send(rank, as_u32(len + 1), data.as_ptr());
}

u32 mpi::Frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<u8> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_RECEIVE(rank, recv_count, count, data, MPI_UINT8_T)
	#endif

	return recv_count;
}

u32 mpi::Frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<u16> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_RECEIVE(rank, recv_count, count, data, MPI_UINT16_T)
	#endif

	return recv_count;
}

u32 mpi::Frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<u32> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_RECEIVE(rank, recv_count, count, data, MPI_UINT32_T)
	#endif

	return recv_count;
}

u32 mpi::Frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<u64> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_RECEIVE(rank, recv_count, count, data, MPI_UINT64_T)
	#endif

	return recv_count;
}

u32 mpi::Frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<s8> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_RECEIVE(rank, recv_count, count, data, MPI_INT8_T)
	#endif

	return recv_count;
}

u32 mpi::Frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<s16> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_RECEIVE(rank, recv_count, count, data, MPI_INT16_T)
	#endif

	return recv_count;
}

u32 mpi::Frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<s32> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_RECEIVE(rank, recv_count, count, data, MPI_INT32_T)
	#endif

	return recv_count;
}

u32 mpi::Frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<s64> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_RECEIVE(rank, recv_count, count, data, MPI_INT64_T)
	#endif

	return recv_count;
}

u32 mpi::Frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] char data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_RECEIVE(rank, recv_count, count, data, MPI_CHAR)
	#endif

	return recv_count;
}

u32 mpi::Frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<f32> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_RECEIVE(rank, recv_count, count, data, MPI_FLOAT)
	#endif

	return recv_count;
}

u32 mpi::Frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<f64> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_RECEIVE(rank, recv_count, count, data, MPI_DOUBLE)
	#endif

	return recv_count;
}

u32 mpi::Frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<f128> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		CALL_SYNC_MPI_RECEIVE(rank, recv_count, count, data, MPI_LONG_DOUBLE)
	#endif

	return recv_count;
}

void mpi::Frontend::receive([[maybe_unused]] u32 rank,
                            [[maybe_unused]] mut<u8> &data) const
{
	u32 info = this->receive(rank, 1, &data);
	assert((info == 0) || (info == 1));
}

void mpi::Frontend::receive([[maybe_unused]] u32 rank,
                            [[maybe_unused]] mut<u16> &data) const
{
	u32 info = this->receive(rank, 1, &data);
	assert((info == 0) || (info == 1));
}

void mpi::Frontend::receive([[maybe_unused]] u32 rank,
                            [[maybe_unused]] mut<u32> &data) const
{
	u32 info = this->receive(rank, 1, &data);
	assert((info == 0) || (info == 1));
}

void mpi::Frontend::receive([[maybe_unused]] u32 rank,
                            [[maybe_unused]] mut<u64> &data) const
{
	u32 info = this->receive(rank, 1, &data);
	assert((info == 0) || (info == 1));
}

void mpi::Frontend::receive([[maybe_unused]] u32 rank,
                            [[maybe_unused]] mut<s8> &data) const
{
	u32 info = this->receive(rank, 1, &data);
	assert((info == 0) || (info == 1));
}

void mpi::Frontend::receive([[maybe_unused]] u32 rank,
                            [[maybe_unused]] mut<s16> &data) const
{
	u32 info = this->receive(rank, 1, &data);
	assert((info == 0) || (info == 1));
}

void mpi::Frontend::receive([[maybe_unused]] u32 rank,
                            [[maybe_unused]] mut<s32> &data) const
{
	u32 info = this->receive(rank, 1, &data);
	assert((info == 0) || (info == 1));
}

void mpi::Frontend::receive([[maybe_unused]] u32 rank,
                            [[maybe_unused]] mut<s64> &data) const
{
	u32 info = this->receive(rank, 1, &data);
	assert((info == 0) || (info == 1));
}

void mpi::Frontend::receive([[maybe_unused]] u32 rank,
                            [[maybe_unused]] char &data) const
{
	u32 info = this->receive(rank, 1, &data);
	assert((info == 0) || (info == 1));
}

void mpi::Frontend::receive([[maybe_unused]] u32 rank,
                            [[maybe_unused]] mut<f32> &data) const
{
	u32 info = this->receive(rank, 1, &data);
	assert((info == 0) || (info == 1));
}

void mpi::Frontend::receive([[maybe_unused]] u32 rank,
                            [[maybe_unused]] mut<f64> &data) const
{
	u32 info = this->receive(rank, 1, &data);
	assert((info == 0) || (info == 1));
}

void mpi::Frontend::receive([[maybe_unused]] u32 rank,
                            [[maybe_unused]] mut<f128> &data) const
{
	u32 info = this->receive(rank, 1, &data);
	assert((info == 0) || (info == 1));
}

// NOTE: For use inside mpi::Frontend::receive() methods only.
#define RECEIVE_VECTOR_DATA(rank, data)                    \
{                                                          \
  mut<usize> new_len = 0;                                  \
                                                           \
  mut<u32> info = this->receive((rank), 1, &new_len);      \
                                                           \
  if (new_len > data.length()) {                           \
    data.resize(new_len);                                  \
  }                                                        \
                                                           \
  info = this->receive((rank), as_u32(new_len), &data[0]); \
                                                           \
  return info;                                             \
}

u32 mpi::Frontend::receive(u32 rank, Vec<u8> &data) const
{
	RECEIVE_VECTOR_DATA(rank, data)
}

u32 mpi::Frontend::receive(u32 rank, Vec<u16> &data) const
{
	RECEIVE_VECTOR_DATA(rank, data)
}

u32 mpi::Frontend::receive(u32 rank, Vec<u32> &data) const
{
	RECEIVE_VECTOR_DATA(rank, data)
}

u32 mpi::Frontend::receive(u32 rank, Vec<u64> &data) const
{
	RECEIVE_VECTOR_DATA(rank, data)
}

u32 mpi::Frontend::receive(u32 rank, Vec<s8> &data) const
{
	RECEIVE_VECTOR_DATA(rank, data)
}

u32 mpi::Frontend::receive(u32 rank, Vec<s16> &data) const
{
	RECEIVE_VECTOR_DATA(rank, data)
}

u32 mpi::Frontend::receive(u32 rank, Vec<s32> &data) const
{
	RECEIVE_VECTOR_DATA(rank, data)
}

u32 mpi::Frontend::receive(u32 rank, Vec<s64> &data) const
{
	RECEIVE_VECTOR_DATA(rank, data)
}

u32 mpi::Frontend::receive(u32 rank, Vec<char> &data) const
{
	RECEIVE_VECTOR_DATA(rank, data);
}

u32 mpi::Frontend::receive(u32 rank, Vec<f32> &data) const
{
	RECEIVE_VECTOR_DATA(rank, data);
}

u32 mpi::Frontend::receive(u32 rank, Vec<f64> &data) const
{
	RECEIVE_VECTOR_DATA(rank, data);
}

u32 mpi::Frontend::receive(u32 rank, Vec<f128> &data) const
{
	RECEIVE_VECTOR_DATA(rank, data);
}

void mpi::Frontend::receive(u32 rank, String &data) const
{
	data.clear();

	mut<u32> info = this->receive(rank, 1, &data.end);

	// NOTE: The string and the null-terminator character are expected.
	usize new_len = data.end + 1;

	if (new_len > data.capacity()) {
		data.resize(new_len);
	}

	info = this->receive(rank, as_u32(new_len), data.as_ptr());

	assert(as_u32(new_len) == info);
}

void mpi::Frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<u8> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_UINT8_T)
	#endif
}

void mpi::Frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<u16> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_UINT16_T)
	#endif
}

void mpi::Frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<u32> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_UINT32_T)
	#endif
}

void mpi::Frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<u64> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_UINT64_T)
	#endif
}

void mpi::Frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<s8> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_INT8_T)
	#endif
}

void mpi::Frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<s16> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_INT16_T)
	#endif
}

void mpi::Frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<s32> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_INT32_T)
	#endif
}

void mpi::Frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<s64> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_INT64_T)
	#endif
}

void mpi::Frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] char data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_CHAR)
	#endif
}

void mpi::Frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<f32> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_FLOAT)
	#endif
}

void mpi::Frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<f64> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_DOUBLE)
	#endif
}

void mpi::Frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<f128> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_LONG_DOUBLE)
	#endif
}

void mpi::Frontend::wait() const
{
	#if defined(USE_MPI)
		#pragma omp critical
		MPI_Barrier(MPI_COMM_WORLD);
	#endif
}

mpi::Frontend::~Frontend()
{
	this->wait();

	#if defined(USE_MPI)
		#pragma omp master
		if (this->rank() == mpi::MASTER_PROCESS_RANK) {
			auto info = 0;

			#if defined(USE_PETSC)
				#if defined(USE_SLEPC)
					info = SlepcFinalize();
					CHECK_PETSC_ERROR("SlepcFinalize()", info)
				#endif

				info = PetscFinalize();
				CHECK_PETSC_ERROR("PetscFinalize()", info)
			#else
				info = MPI_Finalize();
				CHECK_MPI_ERROR("MPI_Finalize()", info)
			#endif
		}
	#endif
}
