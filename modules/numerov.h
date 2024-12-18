#if !defined(NUMEROV_HEADER)
	#define NUMEROV_HEADER
	#include "essentials.h"
	#include "fgh.h"

	namespace numerov {
		// NOTE: The first file format is intended for input coupling potentials,
		// the second for output Numerov ratio matrices and the third for S-matrices.
		constexpr u8 FORMAT_VERSION = 3;

		constexpr u32 MAGIC_NUMBER = 1701998454u;

		struct Basis {
			String filename;
			Vec<fgh::BasisEntry> list;

			Basis(String &filename);
		};

		struct PotentialEntry {
			mut<f64> R;
			Mat<f64> value;
			mut<usize> index;

			PotentialEntry(usize channel_count);
		};

		class Potential {
			public:
			Potential(c_str filename, u8 fmt_ver = 1);

			c_str filename() const;

			f64 reduced_mass();

			usize channel_count() const;

			Range<f64> grid_range();

			const PotentialEntry& operator[](usize grid_index);

			private:
			file::Input input;
			PotentialEntry entry;
		};

		struct RatioEntry {
			mut<f64> R;
			mut<f64> energy;
			Mat<f64> value;

			RatioEntry(usize channel_count);

			usize size() const;
		};

		class Ratio {
			public:
			Ratio(c_str filename, u8 fmt_ver = 2);

			c_str filename() const;

			f64 reduced_mass();

			usize channel_count() const;

			Range<f64> grid_range();

			Range<f64> energy_range();

			const RatioEntry& last_entry(usize energy_index);

			const RatioEntry& operator()(usize grid_index, usize energy_index);

			private:
			mut<usize> stride;
			file::Input input;
			RatioEntry entry;
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

		inline static f64 wavenumber(f64 mass, f64 total_energy, f64 eigenval)
		{
			return std::sqrt(2.0*mass*(total_energy - eigenval));
		}
	}
#endif
