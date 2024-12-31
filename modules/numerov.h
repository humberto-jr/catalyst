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
			const String filename;
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

			const RatioEntry& operator()(usize grid_index, usize energy_index);

			private:
			mut<usize> stride;
			file::Input input;
			RatioEntry entry;
		};

		struct ScattMatrixEntry {
			mut<usize> size;
			mut<usize> channel_count;

			mut<f64> mass;

			mut<u32> j_in;
			mut<u32> v_in;
			mut<u32> J_in;
			mut<u32> l_in;
			mut<s32> p_in;
			mut<u32> n_in;
			mut<f64> eigenval_in;

			mut<u32> j_out;
			mut<u32> v_out;
			mut<u32> J_out;
			mut<u32> l_out;
			mut<s32> p_out;
			mut<u32> n_out;
			mut<f64> eigenval_out;

			Vec<f64> total_energy;
			Vec<c64> value;
		};

		class ScattMatrix {
			public:
			ScattMatrix(c_str filename, u8 fmt_ver = 3);

			c_str filename() const;

			f64 reduced_mass() const;

			usize channel_count() const;

			usize energy_count() const;

			const ScattMatrixEntry& operator()(usize channel_a, usize channel_b);

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
			ScattAmplitude(u32 j_in, u32 j_out, usize theta_count, usize energy_count);

			usize mm_count() const;

			usize theta_count() const;

			usize energy_count() const;

			c64 mm_sum(usize theta_index, usize energy_index) const;

			const ScattAmplitudeEntry& operator()(usize mm_index) const;

			Vec<c64>& operator()(usize mm_index, usize theta_index) const;

			c64& operator()(usize mm_index, usize theta_index, usize energy_index) const;

			private:
			Vec<ScattAmplitudeEntry> entry;
		};

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
