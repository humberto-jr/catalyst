#if !defined(SPLINE_HEADER)
	#define SPLINE_HEADER
	#include "essentials.h"

	class spline {
		public:
		spline(vec<f64> &x, vec<f64> &f);

		spline(spline &&other);

		const vec<f64>& abscissa();

		const vec<f64>& ordinate();

		void use_akima();

		void use_cspline();

		void use_steffen();

		f64 operator()(f64 x) const;

		f64 derivative(f64 x, u8 order = 1) const;

		f64 integral(f64 a, f64 b) const;

		~spline();

		private:
		vec<f64> x;
		vec<f64> f;
		void *data;
		void *state;
	};
#endif
