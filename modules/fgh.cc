#include "fgh.h"
#include "math.h"

void fgh::matrix(f64 mass, f64 step, const vec64 &potential, mat64 &result)
{
	// References:
	// [1] Dulieu et al., J. Chem. Phys. 103, 1 (1995)
	// [2] Marston et al., J. Chem. Phys. 91, 3571 (1989)

	usize size = potential.length();

	assert(result.rows() == size);

	f64 length = as_f64(size - 1)*step;

	f64 factor = (math::PI*math::PI)/(mass*length*length);

	f64 nn_term = factor*as_f64(size*size + 2)/6.0;

	for (mut<usize> n = 0; n < size; ++n) {
		result(n, n) = nn_term + potential[n];

		for (mut<usize> m = (n + 1); m < size; ++m) {
			s32 nm = as_s32(n + 1) - as_s32(m + 1);

			f64 nm_term = std::sin(as_f64(nm)*math::PI/as_f64(size));

			result(n, m) = std::pow(-1.0, nm)*factor/(nm_term*nm_term);
			result(m, n) = result(n, m);
		}
	}
}

void fgh::matrix(f64 mass, f64 step, const vec<mat64> &potential, mat64 &result)
{
	// References:
	// [1] O. Dulieu et al., J. Chem. Phys. 103, 1 (1995)
	// [2] Monnerville et al., J. Chem. Phys. 101, 7580 (1994)

	usize size = potential.length();

	usize states = potential[0].rows();

	assert(result.rows() == states*size);

	f64 length = as_f64(size - 1)*step;

	f64 factor = (math::PI*math::PI)/(mass*length*length);

	f64 nn_term = factor*as_f64(size*size + 2)/6.0;

	mut<usize> row = 0;
	for (mut<usize> p = 0; p < states; ++p) {
		for (mut<usize> n = 0; n < size; ++n) {

			mut<usize> col = 0;
			for (mut<usize> q = 0; q < states; ++q) {

				// NOTE: The energy at the n-th grid point of the pq-pair of states.
				f64 pot_term = potential[n](p, q);

				for (mut<usize> m = 0; m < size; ++m) {
					mut<f64> pnqm = 0.0;

					if ((n == m) && (p == q)) {
						pnqm = nn_term + pot_term;
					}

					if ((n != m) && (p == q)) {
						s32 nm = as_s32(n + 1) - as_s32(m + 1);

						f64 nm_term = std::sin(as_f64(nm)*math::PI/as_f64(size));

						pnqm = std::pow(-1.0, nm)*factor/(nm_term*nm_term);
					}

					if ((n == m) && (p != q)) {
						pnqm = pot_term;
					}

					result(row, col) = pnqm;
					++col;
				}
			}

			++row;
		}
	}
}
