#include <Point2D.h>

bool Point2D::operator==(const Point2D & point)
{
	return ((x == point.x) && (y == point.y));
}

bool Point2D::operator>(const Point2D & point)
{
	return (x>point.x) || ((x>point.x) && (y>point.y));
}

bool Point2D::operator<(const Point2D & point)
{
	return (x<point.x) || ((x<point.x) && (y<point.y));
}

Point2D Point2D::operator+(const Point2D & point)
{
	return Point2D(x + point.x, y + point.y);
}

Point2D Point2D::operator-(const Point2D & point)
{
	return Point2D(x - point.x, y - point.y);
}

/*
inline std::ostream& operator << (std::ostream& os, const Point2D & point)
{
	os << point.x << " " << point.y << std::endl;
	return os;
}
*/
