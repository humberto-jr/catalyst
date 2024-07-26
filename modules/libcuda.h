#if !defined(LIBCUDA_HEADER) && defined(USE_CUDA)
	#define LIBCUDA_HEADER
	#include "essentials.h"
	#include <cuda_runtime.h>

	// NOTE: This header is to be included only during compilations with the nvcc
	// compiler and when the USE_CUDA macro is set. However, it comprises safe
	// wrappers over the CUDA API for use, preferably, from host and device code.

	#define ALL __host__ __device__

	#define CHECK_CUDA_ERROR(name, code)                                                 \
	{                                                                                    \
	  if ((code) != cudaSuccess) {                                                       \
	    print::error(WHERE, (name), " failed with error code ", cudaGetErrorName(code)); \
	  }                                                                                  \
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
			ALL inline dev(usize count = 1): len(count), buf(cuda::malloc<T>(count)), stream(0)
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

			ALL void async_memcpy_to(mut<T> &dest)
			{
				usize count = std::min(sizeof(T), this->size());

				auto info = cudaMemcpyAsync(as_void(&dest), as_void(this->buf), count, cudaMemcpyDeviceToHost, this->stream);

				CHECK_CUDA_ERROR("cudaMemcpyAsync()", info)
			}

			ALL void async_memcpy_to(vec<T> &dest)
			{
				usize count = std::min(dest.size(), this->size());

				auto info = cudaMemcpyAsync(as_void(&dest[0]), as_void(this->buf), count, cudaMemcpyDeviceToHost, this->stream);

				CHECK_CUDA_ERROR("cudaMemcpyAsync()", info)
			}

			ALL void async_memcpy_to(mat<T> &dest)
			{
				usize count = std::min(dest.size(), this->size());

				auto info = cudaMemcpyAsync(as_void(&dest[0]), as_void(this->buf), count, cudaMemcpyDeviceToHost, this->stream);

				CHECK_CUDA_ERROR("cudaMemcpyAsync()", info)
			}

			ALL void async_memcpy_to(dev<T> &dest)
			{
				usize count = std::min(dest.size(), this->size());

				auto info = cudaMemcpyAsync(as_void(dest.buf), as_void(this->buf), count, cudaMemcpyDeviceToDevice, dest.stream);

				CHECK_CUDA_ERROR("cudaMemcpyAsync()", info)
			}

			ALL void wait() const
			{
				auto info = cudaStreamSynchronize(this->stream);

				CHECK_CUDA_ERROR("cudaStreamSynchronize()", info)
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
		};
	}

	#undef ALL
	#undef CHECK_CUDA_ERROR
#endif
