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

	// NOTE: For use inside mpi::frontend methods only.
	#define CHECK_PETSC_ERROR(name, code)                                                                \
	{                                                                                                    \
	  if ((code) != 0) {                                                                                 \
	    print::error(WHERE, "At rank ", this->rank(), ": ", name, "() failed with error code ", (code)); \
	  }                                                                                                  \
	}
#endif

#define CALL_MPI_BROADCAST(rank, count, buffer, datatype)                            \
{                                                                                    \
  auto info = MPI_Bcast(as_void(buffer), (count), datatype, (rank), MPI_COMM_WORLD); \
                                                                                     \
  if (info != MPI_SUCCESS) {                                                         \
    print::error(WHERE, "MPI_Bcast() failed with error code ", info);                \
  }                                                                                  \
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

mpi::frontend::frontend(mut<s32> *argc, char **argv[]):
	my_rank(0), comm_size(1), total_tasks(1)
{
	assert(*argc > -1);
	assert(argv != nullptr);

	#if defined(USE_MPI)
		#if !defined(USE_PETSC)
			// NOTE: The process may be multi-threaded, and multiple threads may
			// make MPI calls, but only one at a time, i.e., MPI calls are not made
			// concurrently from two distinct threads (all MPI calls are serialized).
			// This module is responsible for reinforcing the correct usage, unless
			// PETSC and SLEPC are used, in which case the thread model is chosen by them.
			mut<s32> thread_level = 0;

			MPI_Init_thread(argc, argv, MPI_THREAD_SERIALIZED, &thread_level);
			assert(thread_level == MPI_THREAD_SERIALIZED);
		#else
			auto info = PetscInitialize(&argc, &argv, nullptr, nullptr);
			CHECK_PETSC_ERROR("PetscInitialize()", info)

			#if defined(USE_SLEPC)
				info = SlepcInitialize(&argc, &argv, nullptr, nullptr);
				CHECK_PETSC_ERROR("SlepcInitialize()", info)
			#endif
		#endif

		#pragma omp master
		{
			MPI_Comm_size(MPI_COMM_WORLD, &this->comm_size);
			MPI_Comm_rank(MPI_COMM_WORLD, &this->my_rank);
		}
	#endif
}

void mpi::frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] u8 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Send(&count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD);
			MPI_Send(&data[0], count, MPI_UINT8_T, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD);
		}
	#endif
}

void mpi::frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] u16 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Send(&count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD);
			MPI_Send(&data[0], count, MPI_UINT16_T, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD);
		}
	#endif
}

void mpi::frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] u32 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Send(&count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD);
			MPI_Send(&data[0], count, MPI_UINT32_T, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD);
		}
	#endif
}

void mpi::frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] u64 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Send(&count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD);
			MPI_Send(&data[0], count, MPI_UINT64_T, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD);
		}
	#endif
}

void mpi::frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] s8 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Send(&count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD);
			MPI_Send(&data[0], count, MPI_INT8_T, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD);
		}
	#endif
}

void mpi::frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] s16 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Send(&count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD);
			MPI_Send(&data[0], count, MPI_INT16_T, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD);
		}
	#endif
}

void mpi::frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] s32 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Send(&count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD);
			MPI_Send(&data[0], count, MPI_INT32_T, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD);
		}
	#endif
}

void mpi::frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] s64 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Send(&count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD);
			MPI_Send(&data[0], count, MPI_INT64_T, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD);
		}
	#endif
}

void mpi::frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] const char data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Send(&count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD);
			MPI_Send(&data[0], count, MPI_CHAR, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD);
		}
	#endif
}

void mpi::frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] f32 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Send(&count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD);
			MPI_Send(&data[0], count, MPI_FLOAT, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD);
		}
	#endif
}

void mpi::frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] f64 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Send(&count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD);
			MPI_Send(&data[0], count, MPI_DOUBLE, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD);
		}
	#endif
}

void mpi::frontend::send([[maybe_unused]] u32 rank,
                         [[maybe_unused]] u32 count,
                         [[maybe_unused]] f128 data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Send(&count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD);
			MPI_Send(&data[0], count, MPI_LONG_DOUBLE, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD);
		}
	#endif
}

u32 mpi::frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<u8> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Recv(&recv_count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			if (recv_count > count) {
				recv_count = count;
			}

			MPI_Recv(&data[0], recv_count, MPI_UINT8_T, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	#endif

	return recv_count;
}

u32 mpi::frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<u16> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Recv(&recv_count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			if (recv_count > count) {
				recv_count = count;
			}

			MPI_Recv(&data[0], recv_count, MPI_UINT16_T, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	#endif

	return recv_count;
}

u32 mpi::frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<u32> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Recv(&recv_count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			if (recv_count > count) {
				recv_count = count;
			}

			MPI_Recv(&data[0], recv_count, MPI_UINT32_T, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	#endif

	return recv_count;
}

u32 mpi::frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<u64> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Recv(&recv_count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			if (recv_count > count) {
				recv_count = count;
			}

			MPI_Recv(&data[0], recv_count, MPI_UINT64_T, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	#endif

	return recv_count;
}

u32 mpi::frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<s8> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Recv(&recv_count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			if (recv_count > count) {
				recv_count = count;
			}

			MPI_Recv(&data[0], recv_count, MPI_INT8_T, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	#endif

	return recv_count;
}

u32 mpi::frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<s16> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Recv(&recv_count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			if (recv_count > count) {
				recv_count = count;
			}

			MPI_Recv(&data[0], recv_count, MPI_INT16_T, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	#endif

	return recv_count;
}

u32 mpi::frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<s32> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Recv(&recv_count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			if (recv_count > count) {
				recv_count = count;
			}

			MPI_Recv(&data[0], recv_count, MPI_INT32_T, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	#endif

	return recv_count;
}

u32 mpi::frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<s64> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Recv(&recv_count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			if (recv_count > count) {
				recv_count = count;
			}

			MPI_Recv(&data[0], recv_count, MPI_INT64_T, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	#endif

	return recv_count;
}

u32 mpi::frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] char data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Recv(&recv_count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			if (recv_count > count) {
				recv_count = count;
			}

			MPI_Recv(&data[0], recv_count, MPI_CHAR, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	#endif

	return recv_count;
}

u32 mpi::frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<f32> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Recv(&recv_count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			if (recv_count > count) {
				recv_count = count;
			}

			MPI_Recv(&data[0], recv_count, MPI_FLOAT, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	#endif

	return recv_count;
}

u32 mpi::frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<f64> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Recv(&recv_count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			if (recv_count > count) {
				recv_count = count;
			}

			MPI_Recv(&data[0], recv_count, MPI_DOUBLE, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	#endif

	return recv_count;
}

u32 mpi::frontend::receive([[maybe_unused]] u32 rank,
                           [[maybe_unused]] u32 count,
                           [[maybe_unused]] mut<f128> data[]) const
{
	mut<u32> recv_count = 0;

	#if defined(USE_MPI)
		#pragma omp critical
		{
			MPI_Recv(&recv_count, 1, MPI_UINT32_T, rank, MESSAGE_COUNT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			if (recv_count > count) {
				recv_count = count;
			}

			MPI_Recv(&data[0], recv_count, MPI_LONG_DOUBLE, rank, MESSAGE_CONTENT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	#endif

	return recv_count;
}

void mpi::frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<u8> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_UINT8_T)
	#endif
}

void mpi::frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<u16> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_UINT16_T)
	#endif
}

void mpi::frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<u32> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_UINT32_T)
	#endif
}

void mpi::frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<u64> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_UINT64_T)
	#endif
}

void mpi::frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<s8> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_INT8_T)
	#endif
}


void mpi::frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<s16> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_INT16_T)
	#endif
}

void mpi::frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<s32> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_INT32_T)
	#endif
}

void mpi::frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<s64> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_INT64_T)
	#endif
}

void mpi::frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] char data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_CHAR)
	#endif
}

void mpi::frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<f32> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_FLOAT)
	#endif
}

void mpi::frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<f64> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_DOUBLE)
	#endif
}

void mpi::frontend::broadcast([[maybe_unused]] u32 rank,
                              [[maybe_unused]] u32 count,
                              [[maybe_unused]] mut<f128> data[]) const
{
	#if defined(USE_MPI)
		#pragma omp critical
		CALL_MPI_BROADCAST(rank, count, data, MPI_LONG_DOUBLE)
	#endif
}

void mpi::frontend::wait() const
{
	#if defined(USE_MPI)
		#pragma omp critical
		MPI_Barrier(MPI_COMM_WORLD);
	#endif
}

mpi::frontend::~frontend()
{
	this->wait();

	#if defined(USE_MPI)
		if (this->rank() == mpi::MASTER_PROCESS_RANK) {
			#if !defined(USE_PETSC)
				#pragma omp master
				MPI_Finalize();
			#else
				// NOTE: We ignore if either PETSc or SLEPc fails to end properly.
				auto info = PETSC_SUCCESS;

				#if defined(USE_SLEPC)
					info = SlepcFinalize();
				#endif

				info = PetscFinalize();
			#endif
		}
	#endif
}
