#pragma once
#include <string>
#include <math.h>

class Point2D
{
private:
	double x, y;
public:
	Point2D(const double& x, const double& y) : x(x), y(y) {}
	explicit Point2D() { x = y = 0; }
	Point2D(const Point2D& point) {
		this->x = point.x;
		this->y = point.y;
	}

	Point2D& operator=(const Point2D& point) noexcept;
	friend Point2D operator-(const Point2D& lhs, const Point2D& rhs);
	friend Point2D operator+(const Point2D& lhs, const Point2D& rhs);
	friend bool operator==(const Point2D& lhs, const Point2D& rhs);

	double get_X() const noexcept;
	double get_Y() const noexcept;

	void set_X(const double& x) noexcept;
	void set_Y(const double& y) noexcept;

	std::string to_string() const noexcept;

	Point2D subtraction(const Point2D& point) const noexcept;

	~Point2D() = default;
};

