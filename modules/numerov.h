#if !defined(NUMEROV_HEADER)
	#define NUMEROV_HEADER
	#include "essentials.h"
	#include "fgh.h"

	namespace numerov {
		// NOTE: The first file format is intended for input coupling potentials,
		// the second for output Numerov ratio matrices and the third for S-matrices.
		constexpr u8 FORMAT_VERSION = 3;

		constexpr u32 MAGIC_NUMBER = 1701998454u;

		using Basis = Vec<fgh::Basis>;

		struct Potential {
			public:
			u32 n_min;
			f64 R_min;
			f64 R_max;
			f64 R_step;
			f64 mass;

			inline Potential(u32 n_min, f64 R_min, f64 R_max, f64 R_step, f64 mass, Mat<f64> &coupling, file::Input &input):
				n_min(n_min), R_min(R_min), R_max(R_max), R_step(R_step), mass(mass), coupling(coupling.move()), input(input)
			{
			}

			inline Potential(numerov::Potential &&other):
				n_min(other.n_min), R_min(other.R_min), R_max(other.R_max), R_step(other.R_step), mass(other.mass), coupling(other.coupling.move()), input(other.input)
			{
			}

			const Mat<f64>& operator[](u32 n);

			inline c_str filename() const
			{
				return this->input.filename.as_cstr();
			}

			private:
			Mat<f64> coupling;
			file::Input input;
		};

		struct Solution {
			public:
			f64 mass;
			f64 R_max;
			f64 R_step;
			f64 E_min;
			f64 E_max;
			f64 E_step;
			mut<f64> energy;
			file::Input input;

			inline Solution(f64 mass, f64 R_max, f64 R_step, f64 E_min, f64 E_max, f64 E_step, file::Input &input, Mat<f64> &ratio):
				mass(mass), R_max(R_max), R_step(R_step), E_min(E_min), E_max(E_max), E_step(E_step), energy(0.0), input(input), ratio(ratio.move())
			{
			}

			inline Solution(numerov::Solution &&other):
				mass(other.mass), R_max(other.R_max), R_step(other.R_step), E_min(other.E_min), E_max(other.E_max), E_step(other.E_step), energy(0.0), input(other.input), ratio(other.ratio.move())
			{
			}

			const Mat<f64>& operator[](u32 n);

			private:
			Mat<f64> ratio;
		};

		struct ScattMatrixEntry {
			mut<usize> size;
			mut<u32> channel_count;

			mut<f64> mass;

			mut<u32> j_in;
			mut<u32> v_in;
			mut<u32> J_in;
			mut<u32> l_in;
			mut<s32> p_in;
			mut<u32> comp_in;
			mut<f64> eigenval_in;

			mut<u32> j_out;
			mut<u32> v_out;
			mut<u32> J_out;
			mut<u32> l_out;
			mut<s32> p_out;
			mut<u32> comp_out;
			mut<f64> eigenval_out;

			Vec<f64> total_energy;
			Vec<c64> value;
		};

		class ScattMatrix {
			public:
			ScattMatrix(c_str filename, u8 fmt_ver = 3);

			c_str filename() const;

			f64 reduced_mass() const;

			u32 channel_count() const;

			u32 energy_count() const;

			const ScattMatrixEntry* operator()(u32 channel_a, u32 channel_b);

			private:
			file::Input input;
			ScattMatrixEntry entry;
		};

		struct ScattAmplitudeEntry {
			mut<s32> m_in;
			mut<s32> m_out;
			Vec<Vec<c64>> value;
		};

		class ScattAmplitude {
			public:
			ScattAmplitude(u32 j_in, u32 j_out, u32 theta_count, u32 energy_count);

			u32 mm_count() const;

			u32 theta_count() const;

			u32 energy_count() const;

			c64 mm_sum(u32 theta_index, u32 energy_index) const;

			ScattAmplitudeEntry& operator()(u32 mm_index) const;

			Vec<c64>& operator()(u32 mm_index, u32 theta_index) const;

			c64& operator()(u32 mm_index, u32 theta_index, u32 energy_index) const;

			private:
			Vec<ScattAmplitudeEntry> entry;
		};

		numerov::Basis open_basis_file(const String &filename);

		numerov::Potential open(String &filename, u8 fmt_ver = 1);

		numerov::Solution open_ratio_file(String &filename, u8 fmt_ver = 2);

		void renormalized(f64 mass,
		                  f64 step,
		                  f64 tot_energy,
		                  const Mat<f64> &pot_energy,
		                  Mat<f64> &workspace,
		                  Mat<f64> &old_ratio,
		                  Mat<f64> &new_ratio);

		usize build_react_matrix(f64 mass,
		                         f64 step,
		                         f64 R_max,
		                         f64 tot_energy,
		                         const Mat<f64> &ratio,
		                         const numerov::Basis &level, Mat<f64> &k);

		void build_scatt_matrix(const Mat<f64> &k,
		                        Mat<f64> &re_s, Mat<f64> &im_s);

		void build_scatt_amplitude(const ScattMatrixEntry &s,
		                           s32 m_in, s32 m_out, f64 theta, f64 phi, Vec<c64> &f);

		void build_cross_section(const numerov::ScattAmplitude &f, u32 j_in,
		                         const Vec<f64> &wavenum_in, const Vec<f64> &wavenum_out,
		                         Mat<c64> &f_sum, Mat<f64> &dif_sigma, Vec<f64> &int_sigma);

		inline static f64 centrifugal_term(f64 l, f64 mass, f64 x)
		{
			return l*(l + 1.0)/(2.0*mass*x*x);
		}

		inline static f64 centrifugal_term(u32 l, f64 mass, f64 x)
		{
			return numerov::centrifugal_term(as_f64(l), mass, x);
		}
	}
#endif
