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

#define CHECK_FILE_HEADER(input, fmt_ver)                                                            \
{                                                                                                    \
  mut<decltype(numerov::MAGIC_NUMBER)> tag = -1;                                                     \
                                                                                                     \
  (input).read(tag);                                                                                 \
                                                                                                     \
  CHECK_FILE_END(input)                                                                              \
                                                                                                     \
  if (tag != numerov::MAGIC_NUMBER) {                                                                \
    print::error(WHERE, (input).filename.as_cstr(), " is not a Numerov file (tag = ", tag, ')');     \
  }                                                                                                  \
                                                                                                     \
  mut<decltype(numerov::FORMAT_VERSION)> ver = -1;                                                   \
                                                                                                     \
  (input).read(ver);                                                                                 \
                                                                                                     \
  CHECK_FILE_END(input)                                                                              \
                                                                                                     \
  if ((ver != (fmt_ver)) || (ver > numerov::FORMAT_VERSION)) {                                       \
    print::error(WHERE, (input).filename.as_cstr(), " does not have a valid format version: ", ver); \
  }                                                                                                  \
}

static constexpr usize FILE_HEADER_OFFSET
	= 2*sizeof(u32) + sizeof(u8) + 4*sizeof(f64) + sizeof(usize);

numerov::Basis numerov::open_basis_file(const String &filename)
{
	file::Input input(filename.as_cstr());

	u32 count = fgh::is_valid(input);

	numerov::Basis list(count);

	fgh::load_basis(0, input, list[0]);

	for (mut<u32> n = 1; n < count; ++n) {
		fgh::load_basis(n, input, list[n]);

		assert(list[n].n_min  == list[n - 1].n_min);
		assert(list[n].r_min  == list[n - 1].r_min);
		assert(list[n].r_max  == list[n - 1].r_max);
		assert(list[n].r_step == list[n - 1].r_step);
	}

	return list;
}

numerov::Potential numerov::open(String &filename, u8 fmt_ver)
{
	// TODO: It is missing the implementation of consuming files with Numerov
	// ratio matrices.
	assert(fmt_ver == 1);

	file::Input buf(filename);

	mut<u32> tag = 0;
	buf.read(tag);

	if ((tag != numerov::MAGIC_NUMBER) || buf.end()) {
		print::error(WHERE, buf.filename.as_cstr(), " does not correspond to a Numerov file");
	}

	mut<u8> ver = 0;
	buf.read(ver);

	if ((ver != fmt_ver) || buf.end()) {
		print::error(WHERE, buf.filename.as_cstr(), " does not have a valid format version");
	}

	mut<u32> n_min = 0;
	buf.read(n_min);

	mut<f64> R_min = 0.0;
	buf.read(R_min);

	mut<f64> R_max = 0.0;
	buf.read(R_max);

	mut<f64> R_step = 0.0;
	buf.read(R_step);

	mut<f64> mass = 0.0;
	buf.read(mass);

	mut<usize> ch_count = 0;
	buf.read(ch_count);

	Mat<f64> coupling(ch_count, ch_count);

	return {n_min, R_min, R_max, R_step, mass, coupling, buf};
}

numerov::Solution numerov::open_ratio_file(String &filename, u8 fmt_ver)
{
	file::Input input(filename);

	mut<u32> tag = 0;
	input.read(tag);

	if ((tag != numerov::MAGIC_NUMBER) || input.end()) {
		print::error(WHERE, input.filename.as_cstr(), " does not correspond to a Numerov file");
	}

	mut<u8> ver = 0;
	input.read(ver);

	if ((ver != fmt_ver) || input.end()) {
		print::error(WHERE, input.filename.as_cstr(), " does not have a valid format version");
	}

	mut<f64> R_max = 0.0;
	input.read(R_max);

	mut<f64> R_step = 0.0;
	input.read(R_step);

	mut<f64> mass = 0.0;
	input.read(mass);

	mut<usize> ch_count = 0;
	input.read(ch_count);

	mut<f64> E_min = 0.0;
	input.read(E_min);

	mut<f64> E_max = 0.0;
	input.read(E_max);

	mut<f64> E_step = 0.0;
	input.read(E_step);

	Mat<f64> ratio(ch_count, ch_count);

	if (input.end()) {
		print::error(WHERE, input.filename.as_cstr(), " has no valid solutions");
	}

	return {mass, R_max, R_step, E_min, E_max, E_step, input, ratio};
}

const Mat<f64>& numerov::Potential::operator[](u32 n)
{
	usize offset = sizeof(u32) + sizeof(f64) + this->coupling.size();

	this->input.seek_set(FILE_HEADER_OFFSET + n*offset);

	mut<u32> n_saved = 0;
	this->input.read(n_saved);

	if (n_saved != n) {
		print::error(WHERE, "Expected n = ", n, ", but received n = ", n_saved, " when reading from ", this->input.filename.as_cstr());
	}

	mut<f64> R = 0.0;
	this->input.read(R);

	this->input.read(this->coupling);

	return this->coupling;
}

const Mat<f64>& numerov::Solution::operator[](u32 n)
{
	constexpr usize RATIO_HEADER_OFFSET
		= sizeof(numerov::MAGIC_NUMBER) + sizeof(numerov::FORMAT_VERSION) + 6*sizeof(f64) + sizeof(usize);

	usize stride = sizeof(u32) + sizeof(f64) + this->ratio.size();

	this->input.seek_set(RATIO_HEADER_OFFSET + n*stride);

	mut<u32> n_saved = 0;
	this->input.read(n_saved);

	if (n_saved != n) {
		print::error(WHERE, "Expected n = ", n, ", but received n = ", n_saved, " when reading from ", this->input.filename.as_cstr());
	}

	this->input.read(this->energy);
	this->input.read(this->ratio);

	return this->ratio;
}

//
// numerov::ScattMatrix:
//

static constexpr usize SMATRIX_HEADER_OFFSET
	= sizeof(numerov::FORMAT_VERSION) + sizeof(numerov::MAGIC_NUMBER) + 2*sizeof(u32) + sizeof(f64);

numerov::ScattMatrix::ScattMatrix(c_str filename, u8 fmt_ver):
	input(filename), entry(type_zeroed<numerov::ScattMatrixEntry>())
{
	CHECK_FILE_HEADER(this->input, fmt_ver);

	this->input.read(this->entry.channel_count);

	mut<u32> energy_count = 0;
	this->input.read(energy_count);

	this->input.read(this->entry.mass);

	CHECK_FILE_END(this->input)

	this->entry.total_energy.resize(energy_count);
	this->entry.value.resize(energy_count);

	// NOTE: For every pair of channels, ab, there must be this number of bytes
	// written in the input file. That is, the size of a numerov::ScattMatrixEntry
	// object (without the 'size' and 'channel_count' members) plus three extra
	// integers stored for internal checks (channels and energy indices, all u32).
	this->entry.size = 12*sizeof(u32) + 2*sizeof(s32) + 2*sizeof(f64) + energy_count*(sizeof(u32) + 3*sizeof(f64));
}

c_str numerov::ScattMatrix::filename() const
{
	return this->input.filename.as_cstr();
}

f64 numerov::ScattMatrix::reduced_mass() const
{
	return this->entry.mass;
}

u32 numerov::ScattMatrix::channel_count() const
{
	return this->entry.channel_count;
}

u32 numerov::ScattMatrix::energy_count() const
{
	return as_u32(this->entry.value.length());
}

const numerov::ScattMatrixEntry* numerov::ScattMatrix::operator()(u32 channel_a, u32 channel_b)
{
	CHECK_FILE_END(this->input)

	// NOTE: Using a row-major layout, where each element is this->entry.size bytes long.
	usize stride = (channel_a*this->entry.channel_count + channel_b)*this->entry.size;

	this->input.seek_set(SMATRIX_HEADER_OFFSET + stride);

	mut<u32> saved_a = u32_max;
	this->input.read(saved_a);

	mut<u32> saved_b = u32_max;
	this->input.read(saved_b);

	CHECK_FILE_END(this->input)

	assert(saved_a == channel_a);
	assert(saved_b == channel_b);

	this->input.read(this->entry.j_in);
	this->input.read(this->entry.v_in);
	this->input.read(this->entry.J_in);
	this->input.read(this->entry.l_in);
	this->input.read(this->entry.p_in);
	this->input.read(this->entry.comp_in);
	this->input.read(this->entry.eigenval_in);

	this->input.read(this->entry.j_out);
	this->input.read(this->entry.v_out);
	this->input.read(this->entry.J_out);
	this->input.read(this->entry.l_out);
	this->input.read(this->entry.p_out);
	this->input.read(this->entry.comp_out);
	this->input.read(this->entry.eigenval_out);

	for (mut<u32> n = 0; n < this->entry.value.length(); ++n) {
		mut<u32> saved_n = u32_max;
		this->input.read(saved_n);

		CHECK_FILE_END(this->input)

		assert(saved_n == n);

		this->input.read(this->entry.total_energy[n]);

		mut<f64> re_s = 0.0;
		this->input.read(re_s);

		mut<f64> im_s = 0.0;
		this->input.read(im_s);

		this->entry.value[n] = c64(re_s, im_s);
	}

	return &this->entry;
}

//
// numerov::ScattAmplitude:
//

numerov::ScattAmplitude::ScattAmplitude(u32 j_in, u32 j_out, u32 theta_count, u32 energy_count):
	entry((2*j_in + 1)*(2*j_out + 1))
{
	mut<u32> mm_index = 0;

	for (mut<s32> m_in = -as_s32(j_in); m_in <= as_s32(j_in); ++m_in) {
		for (mut<s32> m_out = -as_s32(j_out); m_out <= as_s32(j_out); ++m_out) {
			Vec<Vec<c64>> theta_list(theta_count);

			this->entry[mm_index].m_in = m_in;
			this->entry[mm_index].m_out = m_out;
			this->entry[mm_index].value.swap(theta_list);

			for (mut<u32> theta_index = 0; theta_index < theta_count; ++theta_index) {
				Vec<c64> energy_list(energy_count);

				this->entry[mm_index].value[theta_index].swap(energy_list);
			}

			mm_index += 1;
		}
	}
}

u32 numerov::ScattAmplitude::mm_count() const
{
	return as_u32(this->entry.length());
}

u32 numerov::ScattAmplitude::theta_count() const
{
	return as_u32(this->entry[0].value.length());
}

u32 numerov::ScattAmplitude::energy_count() const
{
	return as_u32(this->entry[0].value[0].length());
}

c64 numerov::ScattAmplitude::mm_sum(u32 theta_index, u32 energy_index) const
{
	mut<c64> sum = c64(0.0, 0.0);

	for (mut<u32> mm_index = 0; mm_index < this->mm_count(); ++mm_index) {
		sum += this->entry[mm_index].value[theta_index][energy_index];
	}

	return sum;
}

numerov::ScattAmplitudeEntry& numerov::ScattAmplitude::operator()(u32 mm_index) const
{
	return this->entry[mm_index];
}

Vec<c64>& numerov::ScattAmplitude::operator()(u32 mm_index, u32 theta_index) const
{
	return this->entry[mm_index].value[theta_index];
}

c64& numerov::ScattAmplitude::operator()(u32 mm_index, u32 theta_index, u32 energy_index) const
{
	return this->entry[mm_index].value[theta_index][energy_index];
}

//
// Public API:
//

void numerov::renormalized(f64 mass,
                           f64 step,
                           f64 tot_energy,
                           const Mat<f64> &pot_energy,
                           Mat<f64> &workspace,
                           Mat<f64> &old_ratio,
                           Mat<f64> &new_ratio)
{
	// NOTE: This routine implements the renormalized Numerov algorithm of Johnson,
	// which propagates the ratio of the wavefunction from a previous grid point to
	// the current one. See Eq. (22) of B.R. Johnson. J. Chem. Phys. 69, 4678 (1978).
	// Quantities cited below such as T, I, U and R (ratio) are defined in Johnson's
	// paper.

	usize ch_count = pot_energy.rows();

	assert(workspace.rows() == ch_count);
	assert(workspace.cols() == ch_count);
	assert(old_ratio.rows() == ch_count);
	assert(old_ratio.cols() == ch_count);
	assert(new_ratio.rows() == ch_count);
	assert(new_ratio.cols() == ch_count);

	//
	// Step 1: Invert the previous R matrix.
	//

	for (mut<usize> ch = 0; ch < ch_count*ch_count; ++ch) {
		if (old_ratio[ch] != 0.0) {
			lapack::sytri(old_ratio);
			break;
		}
	}

	//
	// Step 2: Build the lhs (I - T) and rhs (2I + 10T) matrices of Eq. (20).
	//

	f64 fact = -step*step*2.0*mass/12.0;

	for (mut<usize> ch_a = 0; ch_a < ch_count; ++ch_a) {
		f64 T = fact*(tot_energy - pot_energy(ch_a, ch_a));

		workspace(ch_a, ch_a) = 1.0 - T;
		new_ratio(ch_a, ch_a) = 2.0 + 10.0*T;

		for (mut<usize> ch_b = (ch_a + 1); ch_b < ch_count; ++ch_b) {
			f64 T = fact*(0.0 - pot_energy(ch_a, ch_b));

			workspace(ch_a, ch_b) = workspace(ch_b, ch_a) = 0.0 - T;
			new_ratio(ch_a, ch_b) = new_ratio(ch_b, ch_a) = 0.0 + 10.0*T;
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

	for (mut<usize> ch_a = 0; ch_a < ch_count; ++ch_a) {
		new_ratio(ch_a, ch_a) -= old_ratio(ch_a, ch_a);

		for (mut<usize> ch_b = (ch_a + 1); ch_b < ch_count; ++ch_b) {
			new_ratio(ch_a, ch_b) -= old_ratio(ch_a, ch_b);
			new_ratio(ch_b, ch_a) -= old_ratio(ch_b, ch_a);
		}
	}
}

usize numerov::build_react_matrix(f64 mass,
                                  f64 step,
                                  f64 R_max,
                                  f64 tot_energy,
                                  const Mat<f64> &ratio,
                                  const numerov::Basis &level, Mat<f64> &k)
{
	// NOTE: This routine implements Johnson's algorithm to compute the augmented
	// reaction matrix K, as in B.R. Johnson. J. Chem. Phys. 69, 4678 (1978). See
	// Appendix A, Eq. (A19). The products Rn and Rj in the paper are named rn and
	// rj below, where R is the ratio of the wavefunction at R_max.

	usize ch_count = ratio.rows();

	assert(k.rows() == ch_count);
	assert(k.cols() == ch_count);
	assert(level.length() == ch_count);

	mut<usize> count = 0;

	f64 R_inf = R_max + step;

	// NOTE: Eq. (17) combined with Eq. (2).
	f64 fact = -step*step*2.0*mass/12.0;

	Mat<f64> n(ch_count, ch_count), j(ch_count, ch_count);

	Mat<f64> rn(ch_count, ch_count), rj(ch_count, ch_count);

	//
	// Step 1: Build the diagonal Riccati-Bessel matrices using Eq. (A16), (A17)
	// and (A20-23).
	//

	for (mut<usize> ch = 0; ch < ch_count; ++ch) {
		f64 l = as_f64(level[ch].l);

		f64 T_max = fact*(
			tot_energy - (level[ch].eigenval + numerov::centrifugal_term(l, mass, R_max))
		);

		f64 T_inf = fact*(
			tot_energy - (level[ch].eigenval + numerov::centrifugal_term(l, mass, R_inf))
		);

		f64 wavenum = numerov::wavenumber(mass, tot_energy, level[ch].eigenval);

		f64 x_max = wavenum*R_max;

		f64 x_inf = wavenum*R_inf;

		if (level[ch].eigenval < tot_energy) {
			++count;

			n(ch, ch) = (1.0 - T_max)*math::riccati_bessel('n', l, x_max);
			j(ch, ch) = (1.0 - T_max)*math::riccati_bessel('j', l, x_max);

			rn(ch, ch) = (1.0 - T_inf)*math::riccati_bessel('n', l, x_inf);
			rj(ch, ch) = (1.0 - T_inf)*math::riccati_bessel('j', l, x_inf);
		} else {
			n(ch, ch) = 1.0;
			j(ch, ch) = 1.0;

			rn(ch, ch) = (1.0 - T_inf)*math::riccati_bessel('n', l, x_inf)/
			             (1.0 - T_max)*math::riccati_bessel('n', l, x_max);

			rj(ch, ch) = (1.0 - T_inf)*math::riccati_bessel('j', l, x_inf)/
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

	usize ch_count = k.rows();

	assert(re_s.rows() == ch_count);
	assert(re_s.cols() == ch_count);
	assert(im_s.rows() == ch_count);
	assert(im_s.cols() == ch_count);

	//
	// Step 1: Compute the square of the K matrix.
	//

	Mat<f64> workspace(ch_count, ch_count);

	blas::gemm<f64>('n', 'n', k, k, workspace);

	//
	// Step 2: Build the (I + K^2) and 2K matrices with re(S) = I temporarily.
	//

	for (mut<usize> ch_a = 0; ch_a < ch_count; ++ch_a) {
		workspace(ch_a, ch_a) += 1.0;

		re_s(ch_a, ch_a) = 1.0;
		im_s(ch_a, ch_a) = 2.0*k(ch_a, ch_a);

		for (mut<usize> ch_b = (ch_a + 1); ch_b < ch_count; ++ch_b) {
			re_s(ch_a, ch_b) = 0.0;
			re_s(ch_b, ch_a) = 0.0;

			im_s(ch_a, ch_b) = 2.0*k(ch_a, ch_b);
			im_s(ch_b, ch_a) = 2.0*k(ch_b, ch_a);
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

	// NOTE: Assuming there are N+1 theta points, which includes both 0 and 180
	// degrees (pi). The theta step size, however, only depends on N.
	u32 theta_count = f.theta_count() - 1u;

	u32 energy_count = f.energy_count();

	assert((theta_count + 1u) == f_sum.rows());

	assert(energy_count == f_sum.cols());

	assert(f_sum.rows() == dif_sigma.rows());

	assert(f_sum.cols() == dif_sigma.cols());

	assert(f_sum.cols() == int_sigma.length());

	f64 j_mult = as_f64(2*j_in + 1);

	Vec<f64> integrand(theta_count + 1u);

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
