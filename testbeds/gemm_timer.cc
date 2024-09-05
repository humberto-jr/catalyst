#include "modules/essentials.h"
#include "modules/libblas.h"
#include "modules/timer.h"

#if defined(USE_CUDA)
	#include "modules/libcuda.h"
#endif

constexpr usize MIN_MATRIX_SIZE = 128;
constexpr usize MAX_MATRIX_SIZE = 2560;
constexpr usize INC_MATRIX_SIZE = 32;

int main()
{
	print::line("# General square matrix-matrix product timer");
	print::line("# Build details:");
	print::line("# Date = ", __DATE__);
	print::line("# File = ", __FILE__);

	#if defined(USE_CUDA)
		cuda::blas::frontend blas(1);
		print::line("# Backend = cuBLAS");
	#else
		switch (blas::BACKEND) {
			case blas::backend::gsl: print::line("# Backend = GNU Scientific Library"); break;

			case blas::backend::mkl: print::line("# Backend = Intel Math Kernel Library"); break;

			case blas::backend::lapack: print::line("# Backend = LAPACK"); break;

			default: print::line("# Backend = Unknown"); break;
		}
	#endif

	print::line("# Size	    Time (s)          Error (avg.)");

	mut<u32> count = 0;
	timer<MAX_MATRIX_SIZE> clock;

	for (mut<usize> n = MIN_MATRIX_SIZE; n < MAX_MATRIX_SIZE; n += INC_MATRIX_SIZE) {
		mat<f64> a(n, n), b(n, n), c(n, n);

		a = 1.0;
		b = 2.0;
		c = 3.0;

		f64 result = as_f64(n)*2.0 + 3.0;

		#if defined(USE_CUDA)
			cuda::dev<f64> a_gpu(n*n), b_gpu(n*n), c_gpu(n*n);

			clock.start();

			a_gpu.async_memcpy_from(a);
			b_gpu.async_memcpy_from(b);
			c_gpu.async_memcpy_from(c);

			blas.gemm<f64>(n, n, n, a_gpu, n, b_gpu, n, c_gpu, n, 1.0, 1.0);

			c_gpu.synchronize();
			c_gpu.async_memcpy_to(c);

			clock.stop();
		#else
			clock.start();
			blas::gemm<f64>('n', 'n', a, b, c, 1.0, 1.0);
			clock.stop();
		#endif

		mut<f64> sum = 0.0;

		for (mut<usize> p = 0; p < n; ++p) {
			for (mut<usize> q = 0; q < n; ++q) {
				f64 diff = c(p, q) - result;

				sum += std::fabs(diff);
			}
		}

		print::line<6>(n, ' ', as_f32(clock[count]), ' ', sum/as_f64(n*n));
		++count;
	}

	print::line("# Total time = ", as_f32(clock.total()), " s");

	return EXIT_SUCCESS;
}
