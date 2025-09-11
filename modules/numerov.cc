#include "liblapack.h"
#include "numerov.h"
#include "libblas.h"
#include "math.h"

#define CHECK_FILE_END(input)                                                                \
{                                                                                            \
  if ((input).end()) {                                                                       \
    print::error(WHERE, "Unexpected end of file when reading ", (input).filename.as_cstr()); \
  }                                                                                          \
}

#define CHECK_DATA_INDEX(input, index, name)                                                                                            \
{                                                                                                                                       \
  mut<usize> saved_index = 0;                                                                                                           \
  (input).read(saved_index);                                                                                                            \
                                                                                                                                        \
  CHECK_FILE_END(input)                                                                                                                 \
                                                                                                                                        \
  if (saved_index != (index)) {                                                                                                         \
    print::error(WHERE, "Expected ", (name), ' ', index, ", but received ", saved_index, " when reading ", (input).filename.as_cstr()); \
  }                                                                                                                                     \
}

#define CHECK_FILE_HEADER(input, fmt_ver)                                                            \
{                                                                                                    \
  mut<decltype(numerov::MAGIC_NUMBER)> tag = 0;                                                      \
                                                                                                     \
  (input).read(tag);                                                                                 \
                                                                                                     \
  CHECK_FILE_END(input)                                                                              \
                                                                                                     \
  if (tag != numerov::MAGIC_NUMBER) {                                                                \
    print::error(WHERE, (input).filename.as_cstr(), " is not a Numerov file (tag = ", tag, ')');     \
  }                                                                                                  \
                                                                                                     \
  mut<decltype(numerov::FORMAT_VERSION)> ver = 0;                                                    \
                                                                                                     \
  (input).read(ver);                                                                                 \
                                                                                                     \
  CHECK_FILE_END(input)                                                                              \
                                                                                                     \
  if ((ver != (fmt_ver)) || (ver > numerov::FORMAT_VERSION)) {                                       \
    print::error(WHERE, (input).filename.as_cstr(), " does not have a valid format version: ", ver); \
  }                                                                                                  \
}

//
// numerov::Basis:
//

numerov::Basis::Basis(String &filename): filename(filename.move())
{
	fgh::Basis basis(this->filename.as_cstr());

	this->list.resize(basis.count());

	for (auto entry : this->list) {
		auto &data = basis[entry.index];

		entry.value.J = data.J;
		entry.value.v = data.v;
		entry.value.n = data.n;
		entry.value.j = data.j;
		entry.value.l = data.l;
		entry.value.p = data.p;
		entry.value.c = data.c;
		entry.value.spin_mult = data.spin_mult;
		entry.value.norm = data.norm;
		entry.value.r_list = data.r_list;
		entry.value.eigenval = data.eigenval;

		entry.value.eigenvec.resize(data.eigenvec.length());

		entry.value.eigenvec = data.eigenvec;
	}
}

//
// numerov::PotentialEntry:
//

numerov::PotentialEntry::PotentialEntry(usize channel_count = 0):
	R(0.0), value(channel_count, channel_count), index(0)
{
}

//
// numerov::Potential:
//

static constexpr usize POTENTIAL_FILE_HEADER = sizeof(numerov::MAGIC_NUMBER)
                                             + sizeof(numerov::FORMAT_VERSION)
                                             + sizeof(usize) + 4*sizeof(f64);

numerov::Potential::Potential(c_str filename, u8 fmt_ver): input(filename)
{
	CHECK_FILE_HEADER(this->input, fmt_ver);

	mut<usize> channel_count = 0;
	this->input.read(channel_count);

	CHECK_FILE_END(this->input)

	this->entry.value.resize(channel_count, channel_count);
}

c_str numerov::Potential::filename() const
{
	return this->input.filename.as_cstr();
}

f64 numerov::Potential::reduced_mass()
{
	this->input.seek_set(POTENTIAL_FILE_HEADER - sizeof(f64));

	CHECK_FILE_END(this->input)

	mut<f64> mass = 0.0;
	this->input.read(mass);

	return mass;
}

usize numerov::Potential::channel_count() const
{
	return this->entry.value.rows();
}

Range<f64> numerov::Potential::grid_range()
{
	this->input.seek_set(POTENTIAL_FILE_HEADER - 4*sizeof(f64));

	CHECK_FILE_END(this->input)

	Range<f64> range;
	this->input.read(range);

	return range;
}

const numerov::PotentialEntry& numerov::Potential::operator[](usize grid_index)
{
	usize stride = sizeof(PotentialEntry::index)
	             + sizeof(PotentialEntry::R) + this->entry.value.size();

	this->input.seek_set(POTENTIAL_FILE_HEADER + grid_index*stride);

	CHECK_DATA_INDEX(this->input, grid_index, "grid index")

	this->input.read(this->entry.R);
	this->input.read(this->entry.value);

	return this->entry;
}

//
// numerov::RatioEntry:
//

numerov::RatioEntry::RatioEntry(usize channel_count = 0):
	R(0.0), energy(0.0), value(channel_count, channel_count)
{
}

usize numerov::RatioEntry::size() const
{
	// NOTE: The ratio entry size in the binary file is that of a RatioEntry struct plus
	// two usize indices tracking the grid and energy indices.
	return 2*sizeof(usize) + sizeof(this->R) + sizeof(this->energy) + this->value.size();
}

//
// numerov::Ratio:
//

static constexpr usize RATIO_FILE_HEADER = sizeof(numerov::MAGIC_NUMBER)
                                         + sizeof(numerov::FORMAT_VERSION)
                                         + sizeof(usize) + sizeof(f64)
                                         + 2*sizeof(Range<f64>);

numerov::Ratio::Ratio(c_str filename, u8 fmt_ver): stride(0), input(filename)
{
	CHECK_FILE_HEADER(this->input, fmt_ver);

	mut<usize> channel_count = 0;
	this->input.read(channel_count);

	CHECK_FILE_END(this->input)

	this->entry.value.resize(channel_count, channel_count);
	this->stride = this->energy_range().count();
}

c_str numerov::Ratio::filename() const
{
	return this->input.filename.as_cstr();
}

f64 numerov::Ratio::reduced_mass()
{
	static constexpr usize HEADER_OFFSET = sizeof(f64) + 2*sizeof(Range<f64>);

	this->input.seek_set(RATIO_FILE_HEADER - HEADER_OFFSET);

	CHECK_FILE_END(this->input)

	mut<f64> mass = 0.0;
	this->input.read(mass);

	return mass;
}

usize numerov::Ratio::channel_count() const
{
	return this->entry.value.rows();
}

Range<f64> numerov::Ratio::grid_range()
{
	static constexpr usize HEADER_OFFSET = 2*sizeof(Range<f64>);

	this->input.seek_set(RATIO_FILE_HEADER - HEADER_OFFSET);

	CHECK_FILE_END(this->input)

	Range<f64> range;
	this->input.read(range);

	return range;
}

Range<f64> numerov::Ratio::energy_range()
{
	static constexpr usize HEADER_OFFSET = sizeof(Range<f64>);

	this->input.seek_set(RATIO_FILE_HEADER - HEADER_OFFSET);

	CHECK_FILE_END(this->input)

	Range<f64> range;
	this->input.read(range);

	return range;
}

const numerov::RatioEntry& numerov::Ratio::operator()(usize grid_index,
                                                      usize energy_index)
{
	// NOTE: The file layout of Numerov solutions is of a matrix of ratio matrices
	// stored in a row-major fashion. Rows store R-dependent entries, and columns
	// are for total-energy-dependent ones. Thus, the size of a row (in bytes) is
	// the number of energies (called stride) times the byte count of one element,
	// which is the size of a RatioEntry struct plus two usize indices tracking the
	// grid and energy indices.
	usize offset = (grid_index*this->stride + energy_index)*this->entry.size();

	this->input.seek_set(RATIO_FILE_HEADER + offset);

	CHECK_DATA_INDEX(this->input, grid_index, "grid index")
	CHECK_DATA_INDEX(this->input, energy_index, "energy index")

	this->input.read(this->entry.R);
	this->input.read(this->entry.energy);
	this->input.read(this->entry.value);

	return this->entry;
}

//
// numerov::ScattMatrix:
//

static constexpr usize SMATRIX_HEADER_OFFSET = sizeof(numerov::FORMAT_VERSION)
                                             + sizeof(numerov::MAGIC_NUMBER)
                                             + 2*sizeof(usize) + sizeof(f64);

numerov::ScattMatrix::ScattMatrix(c_str filename, u8 fmt_ver):
	input(filename), entry(type_zeroed<numerov::ScattMatrixEntry>())
{
	CHECK_FILE_HEADER(this->input, fmt_ver);

	this->input.read(this->entry.channel_count);

	mut<usize> energy_count = 0;
	this->input.read(energy_count);

	this->input.read(this->entry.mass);

	CHECK_FILE_END(this->input)

	this->entry.total_energy.resize(energy_count);
	this->entry.value.resize(energy_count);

	// NOTE: For every pair of channels, ab, there must be this number of bytes
	// written in the input file. That is, the size of a numerov::ScattMatrixEntry
	// object (without the 'size' and 'channel_count' members) plus three extra
	// integers stored for internal checks (channels and energy indices, all usize).
	this->entry.size = 2*sizeof(usize) + 10*sizeof(u32) + 2*sizeof(s32)
	                 + 2*sizeof(f64) + energy_count*(sizeof(usize) + 3*sizeof(f64));
}

c_str numerov::ScattMatrix::filename() const
{
	return this->input.filename.as_cstr();
}

f64 numerov::ScattMatrix::reduced_mass() const
{
	return this->entry.mass;
}

usize numerov::ScattMatrix::channel_count() const
{
	return this->entry.channel_count;
}

usize numerov::ScattMatrix::energy_count() const
{
	return this->entry.value.length();
}

const numerov::ScattMatrixEntry& numerov::ScattMatrix::operator()(usize channel_a,
                                                                  usize channel_b)
{
	// NOTE: Using a row-major layout, where each element is this->entry.size long.
	usize stride = (channel_a*this->entry.channel_count + channel_b)*this->entry.size;

	this->input.seek_set(SMATRIX_HEADER_OFFSET + stride);

	CHECK_DATA_INDEX(this->input, channel_a, "channel a")
	CHECK_DATA_INDEX(this->input, channel_b, "channel b")

	this->input.read(this->entry.j_in);
	this->input.read(this->entry.v_in);
	this->input.read(this->entry.J_in);
	this->input.read(this->entry.l_in);
	this->input.read(this->entry.p_in);
	this->input.read(this->entry.n_in);
	this->input.read(this->entry.eigenval_in);

	this->input.read(this->entry.j_out);
	this->input.read(this->entry.v_out);
	this->input.read(this->entry.J_out);
	this->input.read(this->entry.l_out);
	this->input.read(this->entry.p_out);
	this->input.read(this->entry.n_out);
	this->input.read(this->entry.eigenval_out);

	for (mut<usize> n = 0; n < this->entry.value.length(); ++n) {
		CHECK_DATA_INDEX(this->input, n, "energy index")

		this->input.read(this->entry.total_energy[n]);

		mut<f64> re_s = 0.0;
		this->input.read(re_s);

		mut<f64> im_s = 0.0;
		this->input.read(im_s);

		this->entry.value[n] = c64(re_s, im_s);
	}

	return this->entry;
}

//
// numerov::ScattAmplitude:
//

numerov::ScattAmplitude::ScattAmplitude(u32 j_in, u32 j_out, usize theta_count, usize energy_count):
	entry((2*j_in + 1)*(2*j_out + 1))
{
	mut<usize> mm_index = 0;

	for (mut<s32> m_in = -as_s32(j_in); m_in <= as_s32(j_in); ++m_in) {
		for (mut<s32> m_out = -as_s32(j_out); m_out <= as_s32(j_out); ++m_out) {
			Vec<Vec<c64>> theta_list(theta_count);

			this->entry[mm_index].m_in = m_in;
			this->entry[mm_index].m_out = m_out;
			this->entry[mm_index].value.swap(theta_list);

			for (mut<usize> theta_index = 0; theta_index < theta_count; ++theta_index) {
				Vec<c64> energy_list(energy_count);

				this->entry[mm_index].value[theta_index].swap(energy_list);
			}

			mm_index += 1;
		}
	}
}

usize numerov::ScattAmplitude::mm_count() const
{
	return this->entry.length();
}

usize numerov::ScattAmplitude::theta_count() const
{
	return this->entry[0].value.length();
}

usize numerov::ScattAmplitude::energy_count() const
{
	return this->entry[0].value[0].length();
}

c64 numerov::ScattAmplitude::mm_sum(usize theta_index, usize energy_index) const
{
	mut<c64> sum = c64(0.0, 0.0);

	for (mut<usize> mm_index = 0; mm_index < this->mm_count(); ++mm_index) {
		sum += this->entry[mm_index].value[theta_index][energy_index];
	}

	return sum;
}

const numerov::ScattAmplitudeEntry& numerov::ScattAmplitude::operator()(usize mm_index) const
{
	return this->entry[mm_index];
}

Vec<c64>& numerov::ScattAmplitude::operator()(usize mm_index, usize theta_index) const
{
	return this->entry[mm_index].value[theta_index];
}

c64& numerov::ScattAmplitude::operator()(usize mm_index, usize theta_index, usize energy_index) const
{
	return this->entry[mm_index].value[theta_index][energy_index];
}

//
// Public API:
//

void numerov::renormalized(f64 mass,
                           f64 step,
                           f64 total_energy,
                           const Mat<f64> &potential,
                           Mat<f64> &workspace,
                           Mat<f64> &old_ratio,
                           Mat<f64> &new_ratio)
{
	// NOTE: This routine implements the renormalized Numerov algorithm of Johnson,
	// which propagates the ratio of the wavefunction from a previous grid point to
	// the current one. See Eq. (22) of B.R. Johnson. J. Chem. Phys. 69, 4678 (1978).
	// Quantities cited below such as T, I, U and R (ratio) are defined in Johnson's
	// paper.

	usize channel_count = potential.rows();

	assert(workspace.rows() == channel_count);
	assert(workspace.cols() == channel_count);
	assert(old_ratio.rows() == channel_count);
	assert(old_ratio.cols() == channel_count);
	assert(new_ratio.rows() == channel_count);
	assert(new_ratio.cols() == channel_count);

	//
	// Step 1: Invert the previous R matrix.
	//

	for (mut<usize> channel = 0; channel < channel_count*channel_count; ++channel) {
		if (old_ratio[channel] != 0.0) {
			lapack::sytri(old_ratio);
			break;
		}
	}

	//
	// Step 2: Build the lhs (I - T) and rhs (2I + 10T) matrices of Eq. (20).
	//

	f64 fact = -step*step*2.0*mass/12.0;

	for (mut<usize> channel_a = 0; channel_a < channel_count; ++channel_a) {
		f64 T = fact*(total_energy - potential(channel_a, channel_a));

		workspace(channel_a, channel_a) = 1.0 - T;
		new_ratio(channel_a, channel_a) = 2.0 + 10.0*T;

		for (mut<usize> channel_b = (channel_a + 1); channel_b < channel_count; ++channel_b) {
			f64 T = fact*(0.0 - potential(channel_a, channel_b));

			workspace(channel_a, channel_b)
				= workspace(channel_b, channel_a) = 0.0 - T;

			new_ratio(channel_a, channel_b)
				= new_ratio(channel_b, channel_a) = 0.0 + 10.0*T;
		}
	}

	//
	// Step 3: Solve the system of linear equations (I - T)U = (2I + 10T) for U;
	// on exit, new_ratio holds U temporarily.
	//

	lapack::gesv(workspace, new_ratio);

	//
	// Step 4: Solve Eq. (22) for R = U - R'.
	//

	for (mut<usize> channel_a = 0; channel_a < channel_count; ++channel_a) {
		new_ratio(channel_a, channel_a) -= old_ratio(channel_a, channel_a);

		for (mut<usize> channel_b = (channel_a + 1); channel_b < channel_count; ++channel_b) {
			new_ratio(channel_a, channel_b) -= old_ratio(channel_a, channel_b);
			new_ratio(channel_b, channel_a) -= old_ratio(channel_b, channel_a);
		}
	}
}

usize numerov::build_react_matrix(f64 mass,
                                  f64 step,
                                  f64 R_max,
                                  f64 total_energy,
                                  const Mat<f64> &ratio,
                                  const numerov::Basis &level, Mat<f64> &k)
{
	// NOTE: This routine implements Johnson's algorithm to compute the augmented
	// reaction matrix K, as in B.R. Johnson. J. Chem. Phys. 69, 4678 (1978). See
	// Appendix A, Eq. (A19). The products Rn and Rj in the paper are named rn and
	// rj below, where R is the ratio of the wavefunction at R_max.

	usize channel_count = ratio.rows();

	assert(k.rows() == channel_count);
	assert(k.cols() == channel_count);
	assert(level.list.length() == channel_count);

	mut<usize> count = 0;

	f64 R_inf = R_max + step;

	// NOTE: Eq. (17) combined with Eq. (2).
	f64 fact = -step*step*2.0*mass/12.0;

	Mat<f64> n(channel_count, channel_count), j(channel_count, channel_count);

	Mat<f64> rn(channel_count, channel_count), rj(channel_count, channel_count);

	//
	// Step 1: Build the diagonal Riccati-Bessel matrices using Eq. (A16), (A17)
	// and (A20-23).
	//

	for (mut<usize> channel = 0; channel < channel_count; ++channel) {
		f64 l = as_f64(level.list[channel].l);

		f64 T_max = fact*(
			total_energy - (level.list[channel].eigenval + numerov::centrifugal_term(l, mass, R_max))
		);

		f64 T_inf = fact*(
			total_energy - (level.list[channel].eigenval + numerov::centrifugal_term(l, mass, R_inf))
		);

		f64 wavenum = numerov::wavenumber(mass, total_energy, level.list[channel].eigenval);

		f64 x_max = wavenum*R_max;

		f64 x_inf = wavenum*R_inf;

		if (level.list[channel].eigenval < total_energy) {
			++count;

			n(channel, channel) = (1.0 - T_max)*math::riccati_bessel('n', l, x_max);
			j(channel, channel) = (1.0 - T_max)*math::riccati_bessel('j', l, x_max);

			rn(channel, channel) = (1.0 - T_inf)*math::riccati_bessel('n', l, x_inf);
			rj(channel, channel) = (1.0 - T_inf)*math::riccati_bessel('j', l, x_inf);
		} else {
			n(channel, channel) = 1.0;
			j(channel, channel) = 1.0;

			rn(channel, channel) = (1.0 - T_inf)*math::riccati_bessel('n', l, x_inf)/
			             (1.0 - T_max)*math::riccati_bessel('n', l, x_max);

			rj(channel, channel) = (1.0 - T_inf)*math::riccati_bessel('j', l, x_inf)/
			             (1.0 - T_max)*math::riccati_bessel('j', l, x_max);
		}
	}

	//
	// Step 2: Compute the (-rn + n) matrix.
	//

	blas::gemm<f64>('n', 'n', ratio, n, rn, -1.0, 1.0);

	//
	// Step 3: Compute the (rj - j) matrix.
	//

	blas::gemm<f64>('n', 'n', ratio, j, rj, 1.0, -1.0);

	//
	// Step 4: Solve the system of linear equations (-rn + n)K = (rj - j) for K.
	//

	lapack::gesv(rn, rj);

	k.swap(rj);

	return count;
}

void numerov::build_scatt_matrix(const Mat<f64> &k,
                                 Mat<f64> &re_s, Mat<f64> &im_s)
{
	// NOTE: This routine computes the scatt. matrix S from the open-open block of
	// the reaction matrix K, as in B.R. Johnson. J. Com. Phys. 13, 445-449 (1973).
	// See Eq. (20).

	usize channel_count = k.rows();

	assert(re_s.rows() == channel_count);
	assert(re_s.cols() == channel_count);
	assert(im_s.rows() == channel_count);
	assert(im_s.cols() == channel_count);

	//
	// Step 1: Compute the square of the K matrix.
	//

	Mat<f64> workspace(channel_count, channel_count);

	blas::gemm<f64>('n', 'n', k, k, workspace);

	//
	// Step 2: Build the (I + K^2) and 2K matrices with re(S) = I temporarily.
	//

	for (mut<usize> channel_a = 0; channel_a < channel_count; ++channel_a) {
		workspace(channel_a, channel_a) += 1.0;

		re_s(channel_a, channel_a) = 1.0;
		im_s(channel_a, channel_a) = 2.0*k(channel_a, channel_a);

		for (mut<usize> channel_b = (channel_a + 1); channel_b < channel_count; ++channel_b) {
			re_s(channel_a, channel_b) = 0.0;
			re_s(channel_b, channel_a) = 0.0;

			im_s(channel_a, channel_b) = 2.0*k(channel_a, channel_b);
			im_s(channel_b, channel_a) = 2.0*k(channel_b, channel_a);
		}
	}

	//
	// Step 3: Solve the system of linear equations (I + K^2)im(S) = 2K for im(S).
	//

	lapack::gesv(workspace, im_s);

	//
	// Step 4: Solve re(S) = I - (K)im(S) = -I + (K)im(S).
	//

	blas::gemm<f64>('n', 'n', k, im_s, re_s, 1.0, -1.0);
}

void numerov::build_scatt_amplitude(const numerov::ScattMatrixEntry &s,
                                    s32 m_in, s32 m_out, f64 theta, f64 phi, Vec<c64> &f)
{
	// NOTE: This routine computes the energy-dependent scatt. amplitude f as a
	// function of the scatt. angles (theta, phi) for a given S-matrix element
	// and projection, m (m'), of the rot. angular momentum state j (j'). For
	// details, see Eq. (19) and (20) of R. T. Pack. J. Chem. Phys. 60, 633–639
	// (1974). The results per energy are added to the current values of f.

	assert(s.J_in == s.J_out);

	assert(m_in >= -as_s32(s.j_in));
	assert(m_in <=  as_s32(s.j_in));

	assert(m_out >= -as_s32(s.j_out));
	assert(m_out <=  as_s32(s.j_out));

	assert(s.value.length() == f.length());

	f64 l_mult = as_f64(2*s.l_in + 1);

	c64 i_pow = std::pow(math::IMAGINARY_UNIT, s.l_in - s.l_out + 1);

	f64 c_in = math::clebsch_gordan_coeff(s.j_in, s.l_in, s.J_in, m_in, 0, m_in);

	f64 c_out = math::clebsch_gordan_coeff(s.j_out, s.l_out, s.J_in, m_out, m_in - m_out, m_in);

	if ((c_in == 0.0) || (c_out == 0.0)) {
		return;
	}

	c64 y = math::sphe_harmonics(s.l_out, m_in - m_out, theta, phi);

	if (y == c64(0.0, 0.0)) {
		return;
	}

	f64 I = ((s.v_in == s.v_out) && (s.j_in == s.j_out) && (s.l_in == s.l_out)? 1.0 : 0.0);

	for (mut<u32> n = 0; n < f.length(); ++n) {
		if ((s.total_energy[n] > s.eigenval_in) && (s.total_energy[n] > s.eigenval_out)) {
			f64 wavenum_in = numerov::wavenumber(s.mass, s.total_energy[n], s.eigenval_in);

			f64 wavenum_out = numerov::wavenumber(s.mass, s.total_energy[n], s.eigenval_out);

			f64 fact = std::sqrt(math::PI*l_mult/(wavenum_in*wavenum_out));

			f[n] += fact*i_pow*c_in*c_out*y*(I - s.value[n]);
		}
	}
}

void numerov::build_cross_section(const numerov::ScattAmplitude &f, u32 j_in,
                                  const Vec<f64> &wavenum_in, const Vec<f64> &wavenum_out,
                                  Mat<c64> &f_sum, Mat<f64> &dif_sigma, Vec<f64> &int_sigma)
{
	// NOTE: This routine computes the differential and integral cross-sections,
	// sigma, from a given scatt. amplitude, f, and the incoming and outgoing
	// wavenumbers. For details, see Eq. (21) and (22) of R. T. Pack. J. Chem.
	// Phys. 60, 633–639 (1974).

	constexpr f64 THETA_MIN = 0.0;
	constexpr f64 THETA_MAX = math::PI;

	// NOTE: Assuming there are N+1 theta points, which includes both 0 and pi.
	// The theta step size, however, only depends on N.
	usize theta_count = f.theta_count() - 1;

	usize energy_count = f.energy_count();

	assert((theta_count + 1) == f_sum.rows());

	assert(energy_count == f_sum.cols());

	assert(f_sum.rows() == dif_sigma.rows());

	assert(f_sum.cols() == dif_sigma.cols());

	assert(f_sum.cols() == int_sigma.length());

	f64 j_mult = as_f64(2*j_in + 1);

	Vec<f64> integrand(theta_count + 1);

	f64 theta_step = (THETA_MAX - THETA_MIN)/as_f64(theta_count);

	for (mut<u32> energy_index = 0; energy_index < energy_count; ++energy_index) {

		f64 fact = wavenum_out[energy_index]/(j_mult*wavenum_in[energy_index]);

		for (mut<u32> theta_index = 0; theta_index <= theta_count; ++theta_index) {
			f64 theta = THETA_MIN + as_f64(theta_index)*theta_step;

			f_sum(theta_index, energy_index) = f.mm_sum(theta_index, energy_index);

			c64 fxf = f_sum(theta_index, energy_index)*f_sum(theta_index, energy_index);

			// Eq. (21)
			dif_sigma(theta_index, energy_index) = fact*std::abs(fxf);

			// Eq. (22)
			integrand[theta_index] = std::sin(theta)*dif_sigma(theta_index, energy_index);
		}

		// NOTE: The result of Eq. (22), where 2pi is the value of the integral over phi.
		int_sigma[energy_index] = 2.0*math::PI*math::simpson(theta_step, integrand);
	}
}
