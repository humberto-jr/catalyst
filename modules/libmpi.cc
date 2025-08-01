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

//
// Sends:
//

#define CALL_SYNC_MPI_SEND(rank, count, buf, datatype)                                        \
{                                                                                             \
  auto info = MPI_Send(&(count), 1, MPI_UINT32_T, (rank), MESSAGE_COUNT_TAG, MPI_COMM_WORLD); \
                                                                                              \
  CHECK_MPI_ERROR("1st MPI_Send()", info)                                                     \
                                                                                              \
  info = MPI_Send((buf), (count), datatype, (rank), MESSAGE_CONTENT_TAG, MPI_COMM_WORLD);     \
                                                                                              \
  CHECK_MPI_ERROR("2nd MPI_Send()", info)                                                     \
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

#undef CALL_SYNC_MPI_SEND

void mpi::Frontend::send(u32 rank, u32 count, const nist::Isotope data[]) const
{
	u16 *buf = reinterpret_cast<u16*>(&data[0]);
	this->send(rank, count, buf);
}

#define FRONTEND_SEND_IMPL(type)                    \
void mpi::Frontend::send(u32 rank, type data) const \
{                                                   \
  this->send(rank, 1, &data);                       \
}

FRONTEND_SEND_IMPL(u8)
FRONTEND_SEND_IMPL(u16)
FRONTEND_SEND_IMPL(u32)
FRONTEND_SEND_IMPL(u64)
FRONTEND_SEND_IMPL(s8)
FRONTEND_SEND_IMPL(s16)
FRONTEND_SEND_IMPL(s32)
FRONTEND_SEND_IMPL(s64)
FRONTEND_SEND_IMPL(const char)
FRONTEND_SEND_IMPL(f32)
FRONTEND_SEND_IMPL(f64)
FRONTEND_SEND_IMPL(f128)
FRONTEND_SEND_IMPL(const nist::Isotope)

#undef FRONTEND_SEND_IMPL

#define FRONTEND_SEND_IMPL(type)                                \
void mpi::Frontend::send(u32 rank, const Vec<type> &data) const \
{                                                               \
  usize len = data.length();                                    \
  this->send(rank, 1, &len);                                    \
  this->send(rank, as_u32(len), &data[0]);                      \
}

FRONTEND_SEND_IMPL(u8)
FRONTEND_SEND_IMPL(u16)
FRONTEND_SEND_IMPL(u32)
FRONTEND_SEND_IMPL(u64)
FRONTEND_SEND_IMPL(s8)
FRONTEND_SEND_IMPL(s16)
FRONTEND_SEND_IMPL(s32)
FRONTEND_SEND_IMPL(s64)
FRONTEND_SEND_IMPL(char)
FRONTEND_SEND_IMPL(f32)
FRONTEND_SEND_IMPL(f64)
FRONTEND_SEND_IMPL(f128)
FRONTEND_SEND_IMPL(nist::Isotope)

#undef FRONTEND_SEND_IMPL

#define FRONTEND_SEND_IMPL(type)                                \
void mpi::Frontend::send(u32 rank, const Mat<type> &data) const \
{                                                               \
  usize rows = data.rows();                                     \
  usize cols = data.cols();                                     \
  this->send(rank, 1, &rows);                                   \
  this->send(rank, 1, &cols);                                   \
  this->send(rank, as_u32(rows*cols), &data[0]);                \
}

FRONTEND_SEND_IMPL(u8)
FRONTEND_SEND_IMPL(u16)
FRONTEND_SEND_IMPL(u32)
FRONTEND_SEND_IMPL(u64)
FRONTEND_SEND_IMPL(s8)
FRONTEND_SEND_IMPL(s16)
FRONTEND_SEND_IMPL(s32)
FRONTEND_SEND_IMPL(s64)
FRONTEND_SEND_IMPL(char)
FRONTEND_SEND_IMPL(f32)
FRONTEND_SEND_IMPL(f64)
FRONTEND_SEND_IMPL(f128)
FRONTEND_SEND_IMPL(nist::Isotope)

#undef FRONTEND_SEND_IMPL

void mpi::Frontend::send(u32 rank, const String &data) const
{
	// NOTE: The string and the null-terminator character are sent.
	auto len = data.length();
	this->send(rank, 1, &len);
	this->send(rank, as_u32(len + 1), data.as_ptr());
}

void mpi::Frontend::send(u32 rank, const Struct &data) const
{
	this->send(rank, as_u32(data.size()), &data[0]);
}

#define FRONTEND_SEND_IMPL(type)                                  \
void mpi::Frontend::send(u32 rank, const Range<type> &data) const \
{                                                                 \
  type buf[3] = {data.min, data.max, data.step};                  \
  this->send(rank, 3, buf);                                       \
}

FRONTEND_SEND_IMPL(u8)
FRONTEND_SEND_IMPL(u16)
FRONTEND_SEND_IMPL(u32)
FRONTEND_SEND_IMPL(u64)
FRONTEND_SEND_IMPL(s8)
FRONTEND_SEND_IMPL(s16)
FRONTEND_SEND_IMPL(s32)
FRONTEND_SEND_IMPL(s64)
FRONTEND_SEND_IMPL(char)
FRONTEND_SEND_IMPL(f32)
FRONTEND_SEND_IMPL(f64)
FRONTEND_SEND_IMPL(f128)

#undef FRONTEND_SEND_IMPL

//
// Receives:
//

#define CALL_SYNC_MPI_RECEIVE(rank, recv_count, count, buf, datatype)                                               \
{                                                                                                                   \
  auto info = MPI_Recv(&recv_count, 1, MPI_UINT32_T, (rank), MESSAGE_COUNT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE); \
                                                                                                                    \
  CHECK_MPI_ERROR("1st MPI_Recv()", info)                                                                           \
                                                                                                                    \
  if ((count) >= recv_count) {                                                                                      \
    info = MPI_Recv((buf), (count), datatype, (rank), MESSAGE_CONTENT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);      \
                                                                                                                    \
    CHECK_MPI_ERROR("2nd MPI_Recv()", info)                                                                         \
  }                                                                                                                 \
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

#undef CALL_SYNC_MPI_RECEIVE

u32 mpi::Frontend::receive(u32 rank, u32 count, nist::Isotope data[]) const
{
	mut<u16> *buf = reinterpret_cast<mut<u16>*>(&data[0]);
	return this->receive(rank, count, buf);
}

#define FRONTEND_RECEIVE_IMPL(type)                          \
void mpi::Frontend::receive(u32 rank, mut<type> &data) const \
{                                                            \
  u32 info = this->receive(rank, 1, &data);                  \
  assert((info == 0) || (info == 1));                        \
}

FRONTEND_RECEIVE_IMPL(u8)
FRONTEND_RECEIVE_IMPL(u16)
FRONTEND_RECEIVE_IMPL(u32)
FRONTEND_RECEIVE_IMPL(u64)
FRONTEND_RECEIVE_IMPL(s8)
FRONTEND_RECEIVE_IMPL(s16)
FRONTEND_RECEIVE_IMPL(s32)
FRONTEND_RECEIVE_IMPL(s64)
FRONTEND_RECEIVE_IMPL(char)
FRONTEND_RECEIVE_IMPL(f32)
FRONTEND_RECEIVE_IMPL(f64)
FRONTEND_RECEIVE_IMPL(f128)
FRONTEND_RECEIVE_IMPL(nist::Isotope)

#undef FRONTEND_RECEIVE_IMPL

#define FRONTEND_RECEIVE_IMPL(type)                         \
u32 mpi::Frontend::receive(u32 rank, Vec<type> &data) const \
{                                                           \
  mut<u32> info = 0;                                        \
  mut<usize> new_len = 0;                                   \
                                                            \
  info = this->receive(rank, 1, &new_len);                  \
                                                            \
  if (info == 0) {                                          \
    return 0;                                               \
  }                                                         \
                                                            \
  if (new_len > data.length()) {                            \
    data.resize(new_len);                                   \
  }                                                         \
                                                            \
  info = this->receive(rank, as_u32(new_len), &data[0]);    \
                                                            \
  return info;                                              \
}

FRONTEND_RECEIVE_IMPL(u8)
FRONTEND_RECEIVE_IMPL(u16)
FRONTEND_RECEIVE_IMPL(u32)
FRONTEND_RECEIVE_IMPL(u64)
FRONTEND_RECEIVE_IMPL(s8)
FRONTEND_RECEIVE_IMPL(s16)
FRONTEND_RECEIVE_IMPL(s32)
FRONTEND_RECEIVE_IMPL(s64)
FRONTEND_RECEIVE_IMPL(char)
FRONTEND_RECEIVE_IMPL(f32)
FRONTEND_RECEIVE_IMPL(f64)
FRONTEND_RECEIVE_IMPL(f128)
FRONTEND_RECEIVE_IMPL(nist::Isotope)

#undef FRONTEND_RECEIVE_IMPL

#define FRONTEND_RECEIVE_IMPL(type)                         \
u32 mpi::Frontend::receive(u32 rank, Mat<type> &data) const \
{                                                           \
  mut<u32> info = 0;                                        \
  mut<usize> rows = 0, cols = 0;                            \
                                                            \
  info = this->receive(rank, 1, &rows);                     \
  info = this->receive(rank, 1, &cols);                     \
                                                            \
  if (info == 0) {                                          \
    return 0;                                               \
  }                                                         \
                                                            \
  if ((rows > data.rows()) || (cols > data.cols())) {       \
    data.resize(rows, cols);                                \
  }                                                         \
                                                            \
  info = this->receive(rank, as_u32(rows*cols), &data[0]);  \
                                                            \
  return info;                                              \
}

FRONTEND_RECEIVE_IMPL(u8)
FRONTEND_RECEIVE_IMPL(u16)
FRONTEND_RECEIVE_IMPL(u32)
FRONTEND_RECEIVE_IMPL(u64)
FRONTEND_RECEIVE_IMPL(s8)
FRONTEND_RECEIVE_IMPL(s16)
FRONTEND_RECEIVE_IMPL(s32)
FRONTEND_RECEIVE_IMPL(s64)
FRONTEND_RECEIVE_IMPL(char)
FRONTEND_RECEIVE_IMPL(f32)
FRONTEND_RECEIVE_IMPL(f64)
FRONTEND_RECEIVE_IMPL(f128)
FRONTEND_RECEIVE_IMPL(nist::Isotope)

#undef FRONTEND_RECEIVE_IMPL

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

void mpi::Frontend::receive(u32 rank, Struct &data) const
{
	u32 info = this->receive(rank, as_u32(data.size()), &data[0]);
	assert((info == 0) || (as_usize(info) == data.size()));
}

#define FRONTEND_RECEIVE_IMPL(type)                            \
void mpi::Frontend::receive(u32 rank, Range<type> &data) const \
{                                                              \
  mut<type> buf[3];                                            \
  auto info = this->receive(rank, 3, buf);                     \
                                                               \
  if (info == 0) {                                             \
    return;                                                    \
  } else {                                                     \
    assert(info == 3);                                         \
  }                                                            \
                                                               \
  data = Range<type>(buf[0], buf[1], buf[2]);                  \
}

FRONTEND_RECEIVE_IMPL(u8)
FRONTEND_RECEIVE_IMPL(u16)
FRONTEND_RECEIVE_IMPL(u32)
FRONTEND_RECEIVE_IMPL(u64)
FRONTEND_RECEIVE_IMPL(s8)
FRONTEND_RECEIVE_IMPL(s16)
FRONTEND_RECEIVE_IMPL(s32)
FRONTEND_RECEIVE_IMPL(s64)
FRONTEND_RECEIVE_IMPL(char)
FRONTEND_RECEIVE_IMPL(f32)
FRONTEND_RECEIVE_IMPL(f64)
FRONTEND_RECEIVE_IMPL(f128)

#undef FRONTEND_RECEIVE_IMPL

//
// Broadcasts:
//

#define CALL_MPI_BROADCAST(rank, count, buf, datatype)                       \
{                                                                            \
  auto info = MPI_Bcast((buf), (count), (datatype), (rank), MPI_COMM_WORLD); \
                                                                             \
  CHECK_MPI_ERROR("MPI_Bcast()", info)                                       \
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

#undef CALL_MPI_BROADCAST

void mpi::Frontend::broadcast(u32 rank, u32 count, nist::Isotope data[]) const
{
	mut<u16> *buf = reinterpret_cast<mut<u16>*>(&data[0]);
	this->broadcast(rank, count, buf);
}

#define FRONTEND_BROADCAST_IMPL(type)                          \
void mpi::Frontend::broadcast(u32 rank, Vec<type> &data) const \
{                                                              \
  this->broadcast(rank, as_u32(data.length()), &data[0]);      \
}

FRONTEND_BROADCAST_IMPL(u8)
FRONTEND_BROADCAST_IMPL(u16)
FRONTEND_BROADCAST_IMPL(u32)
FRONTEND_BROADCAST_IMPL(u64)
FRONTEND_BROADCAST_IMPL(s8)
FRONTEND_BROADCAST_IMPL(s16)
FRONTEND_BROADCAST_IMPL(s32)
FRONTEND_BROADCAST_IMPL(s64)
FRONTEND_BROADCAST_IMPL(char)
FRONTEND_BROADCAST_IMPL(f32)
FRONTEND_BROADCAST_IMPL(f64)
FRONTEND_BROADCAST_IMPL(f128)
FRONTEND_BROADCAST_IMPL(nist::Isotope)

#undef FRONTEND_BROADCAST_IMPL

#define FRONTEND_BROADCAST_IMPL(type)                                             \
void mpi::Frontend::broadcast(u32 rank, Mat<type> &data) const                    \
{                                                                                 \
  mut<usize> rows = (this->rank() == rank? data.rows() : 0);                      \
  mut<usize> cols = (this->rank() == rank? data.cols() : 0);                      \
                                                                                  \
  this->broadcast(rank, 1, &rows);                                                \
  this->broadcast(rank, 1, &cols);                                                \
                                                                                  \
  if ((this->rank() != rank) && ((rows > data.rows()) || (cols > data.cols()))) { \
    data.resize(rows, cols);                                                      \
  }                                                                               \
                                                                                  \
  this->broadcast(rank, as_u32(rows*cols), &data[0]);                             \
}

FRONTEND_BROADCAST_IMPL(u8)
FRONTEND_BROADCAST_IMPL(u16)
FRONTEND_BROADCAST_IMPL(u32)
FRONTEND_BROADCAST_IMPL(u64)
FRONTEND_BROADCAST_IMPL(s8)
FRONTEND_BROADCAST_IMPL(s16)
FRONTEND_BROADCAST_IMPL(s32)
FRONTEND_BROADCAST_IMPL(s64)
FRONTEND_BROADCAST_IMPL(char)
FRONTEND_BROADCAST_IMPL(f32)
FRONTEND_BROADCAST_IMPL(f64)
FRONTEND_BROADCAST_IMPL(f128)
FRONTEND_BROADCAST_IMPL(nist::Isotope)

#undef FRONTEND_BROADCAST_IMPL

void mpi::Frontend::broadcast(u32 rank, String &data) const
{
	mut<usize> len = (this->rank() == rank? data.length() + 1 : 0);

	this->broadcast(rank, 1, &len);

	if (this->rank() != rank) {
		data.clear();

		if (len > data.capacity()) {
			data.resize(len);
		}
	}

	this->broadcast(rank, as_u32(len), data.as_ptr());
}

void mpi::Frontend::broadcast(u32 rank, Struct &data) const
{
	this->broadcast(rank, as_u32(data.size()), &data[0]);
}

//
// Gathers:
//

#define CALL_MPI_GATHER(rank, count, buf, datatype)                                                               \
{                                                                                                                 \
  mut<u32> sendcount = 0, recvcount = 0;                                                                          \
                                                                                                                  \
  void *recvbuf = nullptr, *sendbuf = nullptr;                                                                    \
                                                                                                                  \
  if (this->rank() == (rank)) {                                                                                   \
    recvbuf = (buf);                                                                                              \
    recvcount = (count);                                                                                          \
  } else {                                                                                                        \
    sendbuf = (buf);                                                                                              \
    sendcount = (count);                                                                                          \
  }                                                                                                               \
                                                                                                                  \
  auto info = MPI_Gather(sendbuf, sendcount, (datatype), recvbuf, recvcount, (datatype), (rank), MPI_COMM_WORLD); \
                                                                                                                  \
  CHECK_MPI_ERROR("MPI_Gather()", info)                                                                           \
}

void mpi::Frontend::gather([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<u8> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_GATHER(rank, count, data, MPI_UINT8_T)
	#endif
}

void mpi::Frontend::gather([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<u16> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_GATHER(rank, count, data, MPI_UINT16_T)
	#endif
}

void mpi::Frontend::gather([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<u32> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_GATHER(rank, count, data, MPI_UINT32_T)
	#endif
}

void mpi::Frontend::gather([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<u64> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_GATHER(rank, count, data, MPI_UINT64_T)
	#endif
}

void mpi::Frontend::gather([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<s8> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_GATHER(rank, count, data, MPI_INT8_T)
	#endif
}

void mpi::Frontend::gather([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<s16> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_GATHER(rank, count, data, MPI_INT16_T)
	#endif
}

void mpi::Frontend::gather([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<s32> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_GATHER(rank, count, data, MPI_INT32_T)
	#endif
}

void mpi::Frontend::gather([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<s64> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_GATHER(rank, count, data, MPI_INT64_T)
	#endif
}

void mpi::Frontend::gather([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] char data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_GATHER(rank, count, data, MPI_CHAR)
	#endif
}

void mpi::Frontend::gather([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<f32> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_GATHER(rank, count, data, MPI_FLOAT)
	#endif
}

void mpi::Frontend::gather([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<f64> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_GATHER(rank, count, data, MPI_DOUBLE)
	#endif
}

void mpi::Frontend::gather([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<f128> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_GATHER(rank, count, data, MPI_LONG_DOUBLE)
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
