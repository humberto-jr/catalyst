#include "spline.h"
#include "libgsl.h"

inline gsl_interp* as_gsl_data(void *data)
{
	return static_cast<gsl_interp*>(data);
}

inline gsl_interp_accel* as_gsl_state(void *state)
{
	return static_cast<gsl_interp_accel*>(state);
}

spline::spline(vec64 &x, vec64 &f):
	x(x.move()), f(f.move()), data(nullptr), state(gsl_interp_accel_alloc())
{
	if (this->state == nullptr) {
		print::error(WHERE, "gsl_interp_accel_alloc() was unable to allocate resources");
	}
}

spline::spline(spline &&other):
	x(other.x.move()), f(other.f.move()), data(other.data), state(other.state)
{
	other.data = other.state = nullptr;
}

const vec64& spline::abscissa()
{
	return this->x;
}

const vec64& spline::ordinate()
{
	return this->f;
}

void spline::use_akima()
{
	auto data = gsl_interp_alloc(gsl_interp_akima, this->x.length());

	if (data == nullptr) {
		print::error(WHERE, "gsl_interp_alloc() was unable to allocate resources");
	}

	auto info = gsl_interp_init(data, &this->x[0], &this->f[0], this->x.length());

	if (info != 0) {
		print::error(WHERE, "gsl_interp_init() failed with error code ", info);
	}

	if (this->data != nullptr) {
		auto old_data = as_gsl_data(this->data);
		gsl_interp_free(old_data);
	}

	this->data = as_void(data);
	this->state = as_void(state);
}

void spline::use_cspline()
{
	auto data = gsl_interp_alloc(gsl_interp_cspline, this->x.length());

	if (data == nullptr) {
		print::error(WHERE, "gsl_interp_alloc() was unable to allocate resources");
	}

	auto info = gsl_interp_init(data, &this->x[0], &this->f[0], this->x.length());

	if (info != 0) {
		print::error(WHERE, "gsl_interp_init() failed with error code ", info);
	}

	if (this->data != nullptr) {
		auto old_data = as_gsl_data(this->data);
		gsl_interp_free(old_data);
	}

	this->data = as_void(data);
	this->state = as_void(state);
}

void spline::use_steffen()
{
	auto data = gsl_interp_alloc(gsl_interp_steffen, this->x.length());

	if (data == nullptr) {
		print::error(WHERE, "gsl_interp_alloc() was unable to allocate resources");
	}

	auto info = gsl_interp_init(data, &this->x[0], &this->f[0], this->x.length());

	if (info != 0) {
		print::error(WHERE, "gsl_interp_init() failed with error code ", info);
	}

	if (this->data != nullptr) {
		auto old_data = as_gsl_data(this->data);
		gsl_interp_free(old_data);
	}

	this->data = as_void(data);
	this->state = as_void(state);
}

f64 spline::operator()(f64 x) const
{
	auto data = as_gsl_data(this->data);
	auto state = as_gsl_state(this->state);

	return gsl_interp_eval(data, &this->x[0], &this->f[0], x, state);
}

f64 spline::derivative(f64 x, u8 order) const
{
	auto data = as_gsl_data(this->data);
	auto state = as_gsl_state(this->state);

	switch (order) {
		case 1: return gsl_interp_eval_deriv(data, &this->x[0], &this->f[0], x, state);
		case 2: return gsl_interp_eval_deriv2(data, &this->x[0], &this->f[0], x, state);

		default:
		print::error(WHERE, "Invalid order ", order);
	}

	return 0.0;
}

f64 spline::integral(f64 a, f64 b) const
{
	auto data = as_gsl_data(this->data);
	auto state = as_gsl_state(this->state);

	return gsl_interp_eval_integ(data, &this->x[0], &this->f[0], a, b, state);
}

spline::~spline()
{
	auto state = as_gsl_state(this->state);

	if (state != nullptr) {
		gsl_interp_accel_free(state);
	}

	auto data = as_gsl_data(this->data);

	if (data != nullptr) {
		gsl_interp_free(data);
	}
}
