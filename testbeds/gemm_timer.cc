#include "modules/essentials.h"
#include "modules/liblapack.h"
#include "modules/timer.h"

constexpr usize MIN_MATRIX_SIZE = 128;
constexpr usize MAX_MATRIX_SIZE = 2560;
constexpr usize INC_MATRIX_SIZE = 32;

int main()
{
	lapack::frontend lapack;

	print::line("# General square matrix-matrix product timer");
	print::line("# Build details:");
	lapack::about();

	print::line("# Size	    Time (s)          Error (avg.)");

	mut<u32> count = 0;
	timer<MAX_MATRIX_SIZE> clock;

	for (mut<usize> n = MIN_MATRIX_SIZE; n < MAX_MATRIX_SIZE; n += INC_MATRIX_SIZE) {
		matrix a(n, n), b(n, n), c(n, n);

		a = 1.0;
		b = 2.0;
		c = 3.0;

		f64 result = as_f64(n)*2.0 + 3.0;

		clock.start();
		lapack.dgemm(a, b, c, 1.0, 1.0);
		clock.stop();

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
