#include "Curve.h"

const Point2D Curve::getPoint(const double t) {
	return Point2D(f_x(t), f_y(t));
}

const double Curve::get_X(const double t)
{
	return f_x(t);
}

const double Curve::get_Y(const double t)
{
	return f_y(t);
}

const double Curve::get_Dfunc(double t, double e)
{
	return ((f_y(t + e) - f_y(t)) / (e)) / 
			((f_x(t + e) - f_x(t)) / (e));
}

const double Curve::get_Ddfunc(double t, double e)
{
	return ((get_Dfunc(t + e, e) - get_Dfunc(t, e)) / (e)) /
			((f_x(t + e) - f_x(t)) / (e));
}
