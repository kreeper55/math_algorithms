#pragma once
#include <functional>
#include "Point2D.h"

class IFunction
{
public:
	IFunction() = default;
	virtual ~IFunction() = default;

	virtual const Point2D getPoint(double t) = 0;

	virtual const double get_X(double t) = 0;

	virtual const double get_Y(double t) = 0;

	virtual const double get_Dfunc(double t, double e = 1e-6) = 0;

	virtual const double get_Ddfunc(double t, double e = 1e-6) = 0;
};

