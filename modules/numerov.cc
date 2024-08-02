#include "numerov.h"
#include "math.h"

static constexpr usize FILE_HEADER_OFFSET
	= 2*sizeof(u32) + sizeof(u8) + 4*sizeof(f64) + sizeof(usize);

numerov::potential numerov::open(string &filename, u8 fmt_ver)
{
	// TODO: It is missing the implementation of consuming files with Numerov
	// ratio matrices.
	assert(fmt_ver == 1);

	file::input buf(filename);

	mut<u32> tag = 0;
	buf.read(tag);

	if ((tag != numerov::MAGIC_NUMBER) || buf.end()) {
		print::error(WHERE, buf.filename.as_cstr(), " does not correspond to a numerov potential file");
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

	mat<f64> coupling(ch_count, ch_count);

	return {n_min, R_min, R_max, R_step, mass, coupling, buf};
}

const mat<f64>& numerov::potential::operator[](u32 n)
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

void numerov::renormalized(f64 mass,
                           f64 step,
                           f64 tot_energy,
                           const mat<f64> &pot_energy,
                           mat<f64> &workspace,
                           mat<f64> &old_ratio,
                           mat<f64> &new_ratio,
                           lapack::frontend &lapack)
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
			lapack.dsytri(old_ratio);
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

	lapack.dgesv(workspace, new_ratio);

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
                                  const mat<f64> &ratio,
                                  const numerov::basis &level,
                                  mat<f64> &k, lapack::frontend &lapack)
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

	mat<f64> n(ch_count, ch_count), j(ch_count, ch_count);

	mat<f64> rn(ch_count, ch_count), rj(ch_count, ch_count);

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

		f64 wavenum = std::sqrt(2.0*mass*(tot_energy - level[ch].eigenval));

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

	lapack.dgemm(ratio, n, rn, -1.0, 1.0);

	//
	// Step 3: Compute the (rj - j) matrix.
	//

	lapack.dgemm(ratio, j, rj, 1.0, -1.0);

	//
	// Step 4: Solve the system of linear equations (-rn + n)K = (rj - j) for K.
	//

	lapack.dgesv(rn, rj);

	k.swap(rj);

	return count;
}

void numerov::build_scatt_matrix(const mat<f64> &k,
                                 mat<f64> &re_s, mat<f64> &im_s, lapack::frontend &lapack)
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

	mat<f64> workspace(ch_count, ch_count);

	lapack.dgemm(k, k, workspace);

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

	lapack.dgesv(workspace, im_s);

	//
	// Step 4: Solve re(S) = I - (K)im(S) = -I + (K)im(S).
	//

	lapack.dgemm(k, im_s, re_s, 1.0, -1.0);
}
