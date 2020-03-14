#include "Point2D.h"

Point2D operator-(const Point2D& lhs, const Point2D& rhs) {
	Point2D result;
	result.set_X(lhs.x - rhs.x);
	result.set_Y(lhs.y - rhs.y);
	return result;
}

Point2D operator+(const Point2D& lhs, const Point2D& rhs) {
	Point2D result;
	result.set_X(lhs.x + rhs.x);
	result.set_Y(lhs.y + rhs.y);
	return result;
}

bool operator==(const Point2D& lhs, const Point2D& rhs) {
	if (&lhs != &rhs) {
		return (lhs.x == rhs.x) && (lhs.y == rhs.y);
	}
	return false;
}

Point2D& Point2D::operator=(const Point2D& point) noexcept {
	if (this != &point) {
		this->x = point.x;
		this->y = point.y;
	}
	return *this;
}

double Point2D::get_X() const noexcept {
	return this->x;
}

double Point2D::get_Y() const noexcept {
	return this->y;
}

void Point2D::set_X(const double& x) noexcept {
	this->x = x;
}

void Point2D::set_Y(const double& y) noexcept {
	this->y = y;
}

std::string Point2D::to_string() const noexcept {
	return std::to_string(x) + "\t" + std::to_string(y);
}

Point2D Point2D::subtraction(const Point2D& point) const noexcept {
	Point2D result(*this);
	result.set_X(this->x - point.x);
	result.set_Y(this->y - point.y);
	return result;
}