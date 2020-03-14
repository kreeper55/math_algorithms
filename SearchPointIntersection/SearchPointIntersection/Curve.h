#pragma once
#include "Function.h"

class Curve : public IFunction
{
private:
	std::function<double(double)> f_x, f_y;
public:
	Curve(std::function<double(double)> f_x, std::function<double(double)> f_y) : f_x(f_x), f_y(f_y) {}

	// Унаследовано через Function
	virtual const Point2D getPoint(const double t) override;

	virtual const double get_X(const double t) override;

	virtual const double get_Y(const double t) override;

	virtual const double get_Dfunc(double t, double e) override;

	virtual const double get_Ddfunc(double t, double e) override;

	~Curve() = default;
};

