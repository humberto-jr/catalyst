#include "fgh.h"
#include "math.h"

void fgh::matrix(f64 mass, f64 step, const Vec<f64> &potential, Mat<f64> &result)
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

void fgh::matrix(f64 mass, f64 step, const Vec<Mat<f64>> &potential, Mat<f64> &result)
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

f64 fgh::norm(f64 step, const Vec<f64> &eigenvec)
{
	mut<usize> n_max = eigenvec.length() - 1;

	while (n_max%3 != 0) {
		--n_max;
	}

	assert(n_max > 2);

	constexpr f64 FACT = 3.0/8.0;

	mut<f64> sum = eigenvec[0]*eigenvec[0];

	for (mut<usize> n = 1; n < (n_max - 3); n += 3) {
		sum += 3.0*eigenvec[n + 0]*eigenvec[n + 0]
		     + 3.0*eigenvec[n + 1]*eigenvec[n + 1]
		     + 2.0*eigenvec[n + 2]*eigenvec[n + 2];
	}

	sum += 3.0*eigenvec[n_max - 1]*eigenvec[n_max - 1];

	sum += eigenvec[n_max]*eigenvec[n_max];

	sum = FACT*step*sum;

	return 1.0/std::sqrt(sum);
}

u32 fgh::is_valid(file::Input &buf)
{
	buf.seek_set();

	mut<u32> tag = 0;
	buf.read(tag);

	if ((tag != fgh::MAGIC_NUMBER) || buf.end()) {
		print::error(WHERE, buf.filename.as_cstr(), " does not correspond to a FGH basis file");
	}

	mut<u8> ver = 0;
	buf.read(ver);

	if ((ver != fgh::FORMAT_VERSION) || buf.end()) {
		print::error(WHERE, buf.filename.as_cstr(), " does not have a valid format version");
	}

	mut<u32> count = 0;
	buf.read(count);

	if ((count == 0) || buf.end()) {
		print::error(WHERE, buf.filename.as_cstr(), " has no basis functions stored");
	}

	return count;
}

void fgh::load_basis(u32 n, file::Input &buf, fgh::Basis &basis)
{
	buf.seek_set(sizeof(fgh::MAGIC_NUMBER) + sizeof(fgh::FORMAT_VERSION) + sizeof(u32));

	buf.read(basis.n_min);
	buf.read(basis.r_min);
	buf.read(basis.r_max);
	buf.read(basis.r_step);

	basis.resize();

	// NOTE: There is an extra u32 entry in each chunk of data for the basis indexing,
	// which is not part of the struct fgh::Basis (see saved_n below).
	usize offset = n*(6*sizeof(u32) + sizeof(s32) + 2*sizeof(f64) + basis.eigenvec.size());

	buf.seek_set(fgh::BASIS_FILE_HEADER + offset);

	mut<u32> saved_n = 0;
	buf.read(saved_n);

	if (saved_n != n) {
		print::error(WHERE, buf.filename.as_cstr(), " layout is inconsistent; expected n = ", n, ", but found n = ", saved_n);
	}

	buf.read(basis.j);
	buf.read(basis.v);
	buf.read(basis.J);
	buf.read(basis.l);
	buf.read(basis.p);
	buf.read(basis.comp);
	buf.read(basis.norm);
	buf.read(basis.eigenval);
	buf.read(basis.eigenvec);
}
