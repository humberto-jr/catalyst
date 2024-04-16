#if !defined(SPLINE_HEADER)
	#define SPLINE_HEADER
	#include "essentials.h"

	class spline {
		public:
		spline(vec64 &x, vec64 &f);

		spline(spline &&other);

		const vec64& abscissa();

		const vec64& ordinate();

		void use_akima();

		void use_cspline();

		void use_steffen();

		f64 operator()(f64 x) const;

		f64 derivative(f64 x, u8 order = 1) const;

		f64 integral(f64 a, f64 b) const;

		~spline();

		private:
		vec64 x;
		vec64 f;
		void *data;
		void *state;
	};
#endif
