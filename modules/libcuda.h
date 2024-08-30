#if !defined(LIBCUDA_HEADER)
	#define LIBCUDA_HEADER
	#include "essentials.h"
	#include <cuda_runtime.h>
	#include <cublas_v2.h>

	// NOTE: This header is to be included only during compilations with the nvcc
	// compiler and when the USE_CUDA macro is set. However, it comprises safe
	// wrappers over the CUDA API for use, preferably, from host and device code.

	#define CPU __host__
	#define GPU __device__
	#define ALL __host__ __device__

	#define CHECK_CUDA_ERROR(name, code)                                                 \
	{                                                                                    \
	  if ((code) != cudaSuccess) {                                                       \
	    print::error(WHERE, (name), " failed with error code ", cudaGetErrorName(code)); \
	  }                                                                                  \
	}

	#define CHECK_CUBLAS_ERROR(name, code)                                                                                     \
	{                                                                                                                          \
	  if ((code) != CUBLAS_STATUS_SUCCESS) {                                                                                   \
	    print::error(WHERE, (name), " failed with error code ", cublasGetStatusName(code), "; ", cublasGetStatusString(code)); \
	  }                                                                                                                        \
	}

	namespace cuda::blas {
		class frontend;
	}

	namespace cuda {
		template<typename T>
		ALL static mut<T>* malloc(usize count = 1)
		{
			void *dev_ptr = nullptr;

			auto info = cudaMalloc(&dev_ptr, sizeof(T)*count);

			CHECK_CUDA_ERROR("cudaMalloc()", info)

			return static_cast<mut<T>*>(dev_ptr);
		}

		template<typename T>
		ALL static void free(T* &dev_ptr)
		{
			auto info = cudaFree(dev_ptr);

			CHECK_CUDA_ERROR("cudaFree()", info)

			dev_ptr = nullptr;
		}

		template<typename T>
		class dev {
			public:
			ALL inline dev(usize count = 1):
				len(count), buf(cuda::malloc<T>(count)), stream(0), operation(CUBLAS_OP_N)
			{
				auto info = cudaStreamCreate(&this->stream);
				CHECK_CUDA_ERROR("cudaStreamCreate()", info)
			}

			ALL inline usize length() const
			{
				return this->len;
			}

			ALL inline usize size() const
			{
				return sizeof(T)*this->len;
			}

			ALL void async_memcpy_from(const T &source)
			{
				usize count = std::min(this->size(), sizeof(T));

				auto info = cudaMemcpyAsync(as_void(this->buf), as_void(&source), count, cudaMemcpyHostToDevice, this->stream);

				CHECK_CUDA_ERROR("cudaMemcpyAsync()", info)
			}

			ALL void async_memcpy_from(const vec<T> &source)
			{
				usize count = std::min(this->size(), source.size());

				auto info = cudaMemcpyAsync(as_void(this->buf), as_void(&source[0]), count, cudaMemcpyHostToDevice, this->stream);

				CHECK_CUDA_ERROR("cudaMemcpyAsync()", info)
			}

			ALL void async_memcpy_from(const mat<T> &source)
			{
				usize count = std::min(this->size(), source.size());

				auto info = cudaMemcpyAsync(as_void(this->buf), as_void(&source[0]), count, cudaMemcpyHostToDevice, this->stream);

				CHECK_CUDA_ERROR("cudaMemcpyAsync()", info)
			}

			ALL void async_memcpy_to(mut<T> &dest) const
			{
				usize count = std::min(sizeof(T), this->size());

				auto info = cudaMemcpyAsync(as_void(&dest), as_void(this->buf), count, cudaMemcpyDeviceToHost, this->stream);

				CHECK_CUDA_ERROR("cudaMemcpyAsync()", info)
			}

			ALL void async_memcpy_to(vec<T> &dest) const
			{
				usize count = std::min(dest.size(), this->size());

				auto info = cudaMemcpyAsync(as_void(&dest[0]), as_void(this->buf), count, cudaMemcpyDeviceToHost, this->stream);

				CHECK_CUDA_ERROR("cudaMemcpyAsync()", info)
			}

			ALL void async_memcpy_to(mat<T> &dest) const
			{
				usize count = std::min(dest.size(), this->size());

				auto info = cudaMemcpyAsync(as_void(&dest[0]), as_void(this->buf), count, cudaMemcpyDeviceToHost, this->stream);

				CHECK_CUDA_ERROR("cudaMemcpyAsync()", info)
			}

			ALL void async_memcpy_to(dev<T> &dest) const
			{
				usize count = std::min(dest.size(), this->size());

				auto info = cudaMemcpyAsync(as_void(dest.buf), as_void(this->buf), count, cudaMemcpyDeviceToDevice, dest.stream);

				CHECK_CUDA_ERROR("cudaMemcpyAsync()", info)
			}

			ALL void synchronize() const
			{
				auto info = cudaStreamSynchronize(this->stream);

				CHECK_CUDA_ERROR("cudaStreamSynchronize()", info)
			}

			ALL inline void as_non_transposed()
			{
				this->operation = CUBLAS_OP_N;
			}

			ALL inline void as_transposed()
			{
				this->operation = CUBLAS_OP_T;
			}

			ALL inline void as_conjugate_transposed()
			{
				static_assert(is_c32<T>() || is_c64<T>());
				this->operation = CUBLAS_OP_C;
			}

			GPU inline mut<T>& operator[](usize n) const
			{
				return this->buf[n];
			}

			ALL ~dev()
			{
				auto info = cudaStreamDestroy(this->stream);

				CHECK_CUDA_ERROR("cudaStreamDestroy()", info)

				cuda::free(this->buf);
			}

			private:
			usize len;
			mut<T> *buf;
			cudaStream_t stream;
			cublasOperation_t operation;

			friend class cuda::blas::frontend;
		};

		namespace blas {
			class frontend {
				public:
				GPU frontend(): thread_count(1u)
				{
					auto info = cublasCreate(&this->handle[0]);
					CHECK_CUBLAS_ERROR("cublasCreate()", info)
				}

				CPU frontend(u32 max_thread): thread_count(max_thread)
				{
					#pragma omp master
					for (mut<u32> thread = 0; thread < max_thread; ++thread) {
						auto info = cublasCreate(&this->handle[thread]);
						CHECK_CUBLAS_ERROR("cublasCreate()", info)
					}
				}

				template<typename T>
				ALL void gemm(usize m, usize n, usize k, const dev<T> &a, usize lda, const dev<T> &b, usize ldb, dev<T> &c, usize ldc, const T alpha = 1.0, const T beta = 0.0)
				{
					#if defined(__CUDA_ARCH__)
						u32 thread = 0u;
						auto info = cublasSetPointerMode(this->handle[thread], CUBLAS_POINTER_MODE_DEVICE);
					#else
						u32 thread = thread_id();
						auto info = cublasSetPointerMode(this->handle[thread], CUBLAS_POINTER_MODE_HOST);
					#endif

					CHECK_CUBLAS_ERROR("cublasSetPointerMode()", info)

					// NOTE: The GEMM operation will be made on the stream of the buffer c. Thus, after calling this
					// function and before accessing the content of c, one must synchronize it first to make sure
					// results are ready.
					info = cublasSetStream(this->handle[thread], c.stream);

					CHECK_CUBLAS_ERROR("cublasSetStream()", info)

					// NOTE: Old asynchronous operations may be ongoing on the buffers a, b, and c. Let's wait those
					// finish before calling cuBLAS.
					a.synchronize();
					b.synchronize();
					c.synchronize();

					if constexpr(is_f32<T>()) {
						info = cublasSgemm(this->handle[thread], a.operation, b.operation, as_s32(m), as_s32(n), as_s32(k),
						                   &alpha, a.buf, as_s32(lda), b.buf, as_s32(ldb), &beta, c.buf, as_s32(ldc));

						CHECK_CUBLAS_ERROR("cublasSgemm()", info)
					} else if constexpr(is_f64<T>()) {
						info = cublasDgemm(this->handle[thread], a.operation, b.operation, as_s32(m), as_s32(n), as_s32(k),
						                   &alpha, a.buf, as_s32(lda), b.buf, as_s32(ldb), &beta, c.buf, as_s32(ldc));

						CHECK_CUBLAS_ERROR("cublasDgemm()", info)
					} else if constexpr(is_c32<T>()) {
						info = cublasCgemm(this->handle[thread], a.operation, b.operation, as_s32(m), as_s32(n), as_s32(k),
						                   &alpha, a.buf, as_s32(lda), b.buf, as_s32(ldb), &beta, c.buf, as_s32(ldc));

						CHECK_CUBLAS_ERROR("cublasCgemm()", info)
					} else if constexpr(is_c64<T>()) {
						info = cublasZgemm(this->handle[thread], a.operation, b.operation, as_s32(m), as_s32(n), as_s32(k),
						                   &alpha, a.buf, as_s32(lda), b.buf, as_s32(ldb), &beta, c.buf, as_s32(ldc));

						CHECK_CUBLAS_ERROR("cublasZgemm()", info)
					} else {
						print::error(WHERE, "Invalid generic type T = ", type_name<T>(), "; expected T = f32 or f64 or c32 or c64");
					}
				}

				ALL ~frontend()
				{
					#if defined(__CUDA_ARCH__)
						auto info = cublasDestroy(this->handle[0]);
						CHECK_CUBLAS_ERROR("cublasDestroy()", info)
					#else
						#pragma omp master
						for (mut<u32> thread = 0; thread < this->thread_count; ++thread) {
							auto info = cublasDestroy(this->handle[thread]);
							CHECK_CUBLAS_ERROR("cublasDestroy()", info)
						}
					#endif
				}

				private:
				u32 thread_count;
				cublasHandle_t handle[MAX_HOST_THREAD_COUNT];
			};
		}
	}

	#undef CPU
	#undef GPU
	#undef ALL
	#undef CHECK_CUDA_ERROR
	#undef CHECK_CUBLAS_ERROR
#endif
