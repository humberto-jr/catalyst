#include "pes.h"
#include "math.h"

//
// pes::frontend:
//

void pes::frontend::start_extern_pes(c_str filename)
{
	this->call_extern_value = nullptr;
	this->call_extern_startup = nullptr;
	this->call_extern_shutdown = nullptr;

	if (this->extern_pes.is_loaded()) {
		// NOTE: Here we try to load the pes_startup(), pes_value() and pes_shutdown() routines
		// from the external PES library. Before giving up if they are not found, we try again
		// appending an underscore for each name in case they were made using old Fortran
		// compilers.

		auto startup = this->extern_pes.find_symbol<pes::pfn_startup>("pes_startup\0");

		if (startup.has_value() == false) {
			startup = this->extern_pes.find_symbol<pes::pfn_startup>("pes_startup_\0");
		}

		if (startup.has_value()) {
			this->call_extern_startup = startup.value();
		} else {
			print::error(WHERE, "Unable to find pes_startup in ", filename);
		}

		auto value = this->extern_pes.find_symbol<pes::pfn_value>("pes_value\0");

		if (value.has_value() == false) {
			value = this->extern_pes.find_symbol<pes::pfn_value>("pes_value_\0");
		}

		if (value.has_value()) {
			this->call_extern_value = value.value();
		} else {
			print::error(WHERE, "Unable to find pes_value in ", filename);
		}

		auto shutdown = this->extern_pes.find_symbol<pes::pfn_shutdown>("pes_shutdown\0");

		if (shutdown.has_value() == false) {
			shutdown = this->extern_pes.find_symbol<pes::pfn_shutdown>("pes_shutdown_\0");
		}

		if (shutdown.has_value()) {
			this->call_extern_shutdown = shutdown.value();
		} else {
			print::error(WHERE, "Unable to find pes_shutdown in ", filename);
		}

		assert(this->call_extern_value != nullptr);
		assert(this->call_extern_startup != nullptr);
		assert(this->call_extern_shutdown != nullptr);

		// NOTE: Next is the first call to the external PES library. It may need to
		// open files, access the standard output and/or perform some computation.
		// It may also have global variables. Thus, only the master thread will make
		// the call.
		#pragma omp master
		this->call_extern_startup();
	} else {
		print::error(WHERE, "Unable to load ", filename);
	}
}

pes::frontend::frontend(const string &filename, const nist::isotope a, const nist::isotope b, const nist::isotope c):
	extern_pes(lib(filename.as_cstr())), a(a), b(b), c(c), mass_a(0.0), mass_b(0.0), mass_c(0.0)
{
	// NOTE: Atomic masses are stored in atomic units.
	this->mass_a = nist::atomic_mass(a)*nist::ATOMIC_MASS_TO_ATOMIC_UNIT;
	this->mass_b = nist::atomic_mass(b)*nist::ATOMIC_MASS_TO_ATOMIC_UNIT;
	this->mass_c = nist::atomic_mass(c)*nist::ATOMIC_MASS_TO_ATOMIC_UNIT;
	this->start_extern_pes(filename.as_cstr());
}

f64 pes::frontend::mass_abc(const char arrang) const
{
	f64 mass_bc  = this->mass_b + this->mass_c;
	f64 mass_ac  = this->mass_a + this->mass_c;
	f64 mass_ab  = this->mass_a + this->mass_b;
	f64 mass_abc = this->mass_a + this->mass_b + this->mass_c;

	switch (arrang) {
		case 'a': return this->mass_a*mass_bc/mass_abc;
		case 'b': return this->mass_b*mass_ac/mass_abc;
		case 'c': return this->mass_c*mass_ab/mass_abc;
		 default: return 0.0;
	}
}

f64 pes::frontend::value(const char arrang, f64 r, f64 R, f64 theta) const
{
	// NOTE: bc = 0, ac = 1, ab = 2.
	mut<f64> internuc[3] = {0.0, 0.0, 0.0};

	f64 th = math::as_rad(theta);

	math::vec3 a, b, c;

	switch (arrang) {
		case 'a': {
			b.x = 0.0;
			b.y = r/2.0;
			b.z = 0.0;

			c.x =  0.0;
			c.y = -b.y;
			c.z =  0.0;

			math::vec3 bc;
			bc.y = (b.y*this->mass_b + c.y*this->mass_c)/(this->mass_b + this->mass_c);

			a.x = bc.x;
			a.y = bc.y + R*std::sin(th);
			a.z = bc.z + R*std::cos(th);

			internuc[0] = r;
			internuc[1] = a - c;
			internuc[2] = a - b;
			break;
		}

		case 'b': {
			a.x = 0.0;
			a.y = r/2.0;
			a.z = 0.0;

			c.x =  0.0;
			c.y = -a.y;
			c.z =  0.0;

			math::vec3 ac;
			ac.y = (a.y*this->mass_a + c.y*this->mass_c)/(this->mass_a + this->mass_c);

			b.x = ac.x;
			b.y = ac.y + R*std::sin(th);
			b.z = ac.z + R*std::cos(th);

			internuc[0] = b - c;
			internuc[1] = r;
			internuc[2] = a - b;
			break;
		}

		case 'c': {
			a.x = 0.0;
			a.y = r/2.0;
			a.z = 0.0;

			b.x =  0.0;
			b.y = -a.y;
			b.z =  0.0;

			math::vec3 ab;
			ab.y = (a.y*this->mass_a + b.y*this->mass_b)/(this->mass_a + this->mass_b);

			c.x = ab.x;
			c.y = ab.y + R*std::sin(th);
			c.z = ab.z + R*std::cos(th);

			internuc[0] = b - c;
			internuc[1] = a - c;
			internuc[2] = r;
			break;
		}

		default:
		print::error(WHERE, "Invalid arrangement ", arrang);
	}

	return this->call_extern_value(internuc);
}

f64 pes::frontend::diatom_bc(u32 j, f64 r) const
{
	f64 m = this->mass_bc();
	u32 b = j*(j + 1);

	return this->value('a', r) + as_f64(b)/(2.0*m*r*r);
}

f64 pes::frontend::diatom_ac(u32 j, f64 r) const
{
	f64 m = this->mass_ac();
	u32 b = j*(j + 1);

	return this->value('b', r) + as_f64(b)/(2.0*m*r*r);
}

f64 pes::frontend::diatom_ab(u32 j, f64 r) const
{
	f64 m = this->mass_ab();
	u32 b = j*(j + 1);

	return this->value('c', r) + as_f64(b)/(2.0*m*r*r);
}

f64 pes::frontend::legendre_multipole_term(const char arrang, u32 lambda, f64 r, f64 R) const
{
	// References:
	// [1] W. H. Miller, J. Chem. Phys., Vol. 50, Num. 1, 407-418 (1969)

	struct legendre {
		const pes::frontend &pes;
		const char arrang;
		u32 lambda;
		f64 r;
		f64 R;
	};

	auto integrand = [](f64 theta, void *params) -> f64 {
		auto input = static_cast<legendre*>(params);

		f64 x = math::as_deg(theta);

		f64 v = input->pes.value(input->arrang, input->r, input->R, x);

		f64 v_inf = input->pes.value(input->arrang, input->r, 1000.0, x);

		return (v_inf - v)*math::legendre_poly(input->lambda, cos(theta))*sin(theta);
	};

	legendre params = {*this, arrang, lambda, r, R};

	f64 result = math::gauss_legendre(0.0, math::PI, 64, as_void(&params), integrand);

	// NOTE: Eq. (22) of [1].
	return as_f64(2*lambda + 1)*result/2.0;
}

pes::frontend::~frontend()
{
	// NOTE: This is the last call to the external PES library.
	#pragma omp master
	this->call_extern_shutdown();
}

//
// Model potentials:
//

f64 pes::olson_smith_pra1971(usize n, usize m, f64 x)
{
	// References:
	// [1] R. E. Olson et al. Phys. Rev. A. 3, 1607 (1971)

	// NOTE: This is the 2x2 model potential of Olson and Smith for the Ne + He^+
	// interaction at a given internuclear distance x. See Eq. (45) and Table I
	// of Ref. [1].

	if ((n == 0) && (m == 0))
		return 21.1*std::exp(-x/0.678)/x;

	else if ((n == 0) && (m == 1))
		return 0.170*std::exp(-x/0.667);

	else if ((n == 1) && (m == 0))
		return 0.170*std::exp(-x/0.667);

	else if ((n == 1) && (m == 1))
		return (21.1/x - 12.1)*std::exp(-x/0.678) + 16.8/nist::HARTREE_TO_EV;

	else
		print::error("Invalid values of n = ", n, " and/or m = ", m);

	// NOTE: Unreachable.
	return 0.0;
}
