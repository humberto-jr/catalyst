#include "fgh.h"
#include "math.h"

#define CHECK_FILE_END(input)                                                                \
{                                                                                            \
  if ((input).end()) {                                                                       \
    print::error(WHERE, "Unexpected end of file when reading ", (input).filename.as_cstr()); \
  }                                                                                          \
}

#define CHECK_FILE_HEADER(input, fmt_ver)                                                            \
{                                                                                                    \
  mut<decltype(fgh::MAGIC_NUMBER)> tag = 0;                                                          \
                                                                                                     \
  (input).read(tag);                                                                                 \
                                                                                                     \
  CHECK_FILE_END(input)                                                                              \
                                                                                                     \
  if (tag != fgh::MAGIC_NUMBER) {                                                                    \
    print::error(WHERE, (input).filename.as_cstr(), " is not a FGH file (tag = ", tag, ')');         \
  }                                                                                                  \
                                                                                                     \
  mut<decltype(fgh::FORMAT_VERSION)> ver = 0;                                                        \
                                                                                                     \
  (input).read(ver);                                                                                 \
                                                                                                     \
  CHECK_FILE_END(input)                                                                              \
                                                                                                     \
  if ((ver != (fmt_ver)) || (ver > fgh::FORMAT_VERSION)) {                                           \
    print::error(WHERE, (input).filename.as_cstr(), " does not have a valid format version: ", ver); \
  }                                                                                                  \
}

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

//
// fgh::Basis:
//

static constexpr usize BASIS_FILE_HEADER = sizeof(fgh::MAGIC_NUMBER)
                                         + sizeof(fgh::FORMAT_VERSION)
                                         + sizeof(usize) + 3*sizeof(f64) + sizeof(u8);

fgh::Basis::Basis(c_str filename, u8 fmt_ver): len(0), stride(0), input(filename)
{
	CHECK_FILE_HEADER(this->input, fmt_ver)

	this->input.read(this->len);

	if (this->len == 0) {
		print::error(WHERE, this->input.filename.as_cstr(), " has no FGH components");
	}

	this->input.read(this->entry.r_list);

	this->input.read(this->entry.spin_mult);

	print::line("SPIN MULT. = ", this->entry.spin_mult);

	this->entry.eigenvec.resize(this->entry.r_list.count());

	// NOTE: There is an extra usize entry used for the basis indexing in each
	// chunk of data stored in the file, which is not part of fgh::BasisEntry.
	this->stride = sizeof(usize)
	             + 6*sizeof(u32)
	             + sizeof(s32) + 2*sizeof(f64) + this->entry.eigenvec.size();

	CHECK_FILE_END(this->input)
}

const fgh::BasisEntry& fgh::Basis::operator[](usize index)
{
	CHECK_FILE_END(this->input)

	this->input.seek_set(BASIS_FILE_HEADER + index*this->stride);

	mut<usize> saved_index = 0;
	this->input.read(saved_index);

	if (saved_index != index) {
		print::error(WHERE, "Expected basis index ", index, ", but received ", saved_index, " when reading from ", this->input.filename.as_cstr());
	}

	this->input.read(this->entry.n);
	this->input.read(this->entry.j);
	this->input.read(this->entry.v);
	this->input.read(this->entry.J);
	this->input.read(this->entry.l);
	this->input.read(this->entry.p);
	this->input.read(this->entry.c);
	this->input.read(this->entry.norm);
	this->input.read(this->entry.eigenval);
	this->input.read(this->entry.eigenvec);

	return this->entry;
}
