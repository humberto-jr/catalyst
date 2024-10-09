#if !defined(NUMEROV_HEADER)
	#define NUMEROV_HEADER
	#include "essentials.h"
	#include "fgh.h"

	namespace numerov {
		// NOTE: The first file format is intended for input coupling potentials,
		// the second for output Numerov ratio matrices and the third for S-matrices.
		constexpr u8 FORMAT_VERSION = 3;

		constexpr u32 MAGIC_NUMBER = 1701998454u;

		using basis = vec<fgh::basis>;

		struct potential {
			public:
			u32 n_min;
			f64 R_min;
			f64 R_max;
			f64 R_step;
			f64 mass;

			inline potential(u32 n_min, f64 R_min, f64 R_max, f64 R_step, f64 mass, mat<f64> &coupling, file::input &input):
				n_min(n_min), R_min(R_min), R_max(R_max), R_step(R_step), mass(mass), coupling(coupling.move()), input(input)
			{
			}

			inline potential(numerov::potential &&other):
				n_min(other.n_min), R_min(other.R_min), R_max(other.R_max), R_step(other.R_step), mass(other.mass), coupling(other.coupling.move()), input(other.input)
			{
			}

			const mat<f64>& operator[](u32 n);

			inline c_str filename() const
			{
				return this->input.filename.as_cstr();
			}

			private:
			mat<f64> coupling;
			file::input input;
		};

		struct solution {
			public:
			f64 mass;
			f64 R_max;
			f64 R_step;
			f64 E_min;
			f64 E_max;
			f64 E_step;
			mut<f64> energy;
			file::input input;

			inline solution(f64 mass, f64 R_max, f64 R_step, f64 E_min, f64 E_max, f64 E_step, file::input &input, mat<f64> &ratio):
				mass(mass), R_max(R_max), R_step(R_step), E_min(E_min), E_max(E_max), E_step(E_step), energy(0.0), input(input), ratio(ratio.move())
			{
			}

			inline solution(numerov::solution &&other):
				mass(other.mass), R_max(other.R_max), R_step(other.R_step), E_min(other.E_min), E_max(other.E_max), E_step(other.E_step), energy(0.0), input(other.input), ratio(other.ratio.move())
			{
			}

			const mat<f64>& operator[](u32 n);

			private:
			mat<f64> ratio;
		};

		struct smatrix_entry {
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

			vec<f64> total_energy;
			vec<c64> value;
		};

		class smatrix {
			public:
			smatrix(c_str filename, u8 fmt_ver = 3);

			c_str filename() const;

			f64 reduced_mass() const;

			u32 channel_count() const;

			u32 energy_count() const;

			const smatrix_entry* operator()(u32 channel_a, u32 channel_b);

			private:
			file::input input;
			smatrix_entry entry;
		};

		struct scatt_amplitude_entry {
			mut<s32> m_in;
			mut<s32> m_out;
			vec<vec<c64>> value;
		};

		class scatt_amplitude {
			public:
			scatt_amplitude(u32 j_in, u32 j_out, u32 theta_count, u32 energy_count);

			u32 mm_count() const;

			u32 theta_count() const;

			u32 energy_count() const;

			c64 mm_sum(u32 theta_index, u32 energy_index) const;

			scatt_amplitude_entry& operator()(u32 mm_index) const;

			vec<c64>& operator()(u32 mm_index, u32 theta_index) const;

			c64& operator()(u32 mm_index, u32 theta_index, u32 energy_index) const;

			private:
			vec<scatt_amplitude_entry> entry;
		};

		numerov::basis open_basis_file(const string &filename);

		numerov::potential open(string &filename, u8 fmt_ver = 1);

		numerov::solution open_ratio_file(string &filename, u8 fmt_ver = 2);

		void renormalized(f64 mass,
		                  f64 step,
		                  f64 tot_energy,
		                  const mat<f64> &pot_energy,
		                  mat<f64> &workspace,
		                  mat<f64> &old_ratio,
		                  mat<f64> &new_ratio);

		usize build_react_matrix(f64 mass,
		                         f64 step,
		                         f64 R_max,
		                         f64 tot_energy,
		                         const mat<f64> &ratio,
		                         const numerov::basis &level, mat<f64> &k);

		void build_scatt_matrix(const mat<f64> &k,
		                        mat<f64> &re_s, mat<f64> &im_s);

		void build_scatt_amplitude(const smatrix_entry &s,
		                           s32 m_in, s32 m_out, f64 theta, f64 phi, vec<c64> &f);

		void build_cross_section(const numerov::scatt_amplitude &f, u32 j_in,
		                         const vec<f64> &wavenum_in, const vec<f64> &wavenum_out,
		                         mat<c64> &f_sum, mat<f64> &dif_sigma, vec<f64> &int_sigma);

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
