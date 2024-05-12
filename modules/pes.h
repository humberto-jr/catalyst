#if !defined(PES_HEADER)
	#define PES_HEADER
	#include "essentials.h"
	#include "nist.h"
	#include "lib.h"

	namespace pes {
		using pfn_startup = void (*)();

		using pfn_value = f64 (*)(f64 x[]);

		using pfn_shutdown = void (*)();

		class frontend {
			public:
			frontend(const string &filename, const nist::isotope a, const nist::isotope b, const nist::isotope c);

			inline c_str filename() const
			{
				return this->extern_pes.filename();
			}

			inline c_str atom_a() const
			{
				return nist::atomic_symbol(this->a);
			}

			inline c_str atom_b() const
			{
				return nist::atomic_symbol(this->b);
			}

			inline c_str atom_c() const
			{
				return nist::atomic_symbol(this->c);
			}

			inline f64 mass_ab() const
			{
				return this->mass_a*this->mass_b/(this->mass_a + this->mass_b);
			}

			inline f64 mass_bc() const
			{
				return this->mass_b*this->mass_c/(this->mass_b + this->mass_c);
			}

			inline f64 mass_ac() const
			{
				return this->mass_a*this->mass_c/(this->mass_a + this->mass_c);
			}

			f64 mass_abc(const char arrang) const;

			f64 value(const char arrang, f64 r, f64 R = 1000.0, f64 theta = 0.0) const;

			f64 diatom_bc(u32 j, f64 r) const;

			f64 diatom_ac(u32 j, f64 r) const;

			f64 diatom_ab(u32 j, f64 r) const;

			f64 legendre_multipole_term(const char arrang, u32 lambda, f64 r, f64 R) const;

			~frontend();

			private:
			lib extern_pes;
			nist::isotope a;
			nist::isotope b;
			nist::isotope c;
			mut<f64> mass_a;
			mut<f64> mass_b;
			mut<f64> mass_c;
			pfn_value call_extern_value;
			pfn_startup call_extern_startup;
			pfn_shutdown call_extern_shutdown;

			void start_extern_pes(c_str filename);
		};

		//
		// Model potentials:
		//

		f64 olson_smith_pra1971(usize n, usize m, f64 x);
	};
#endif
