#pragma once
#include <pixel.h>
#include <Line.h>
#include <vector>

namespace Transform
{
	Point2D transform(double (*mat)[3], const Point2D & point);

	Point2D translate(const Point2D & point, int tx, int ty);
	std::vector<Point2D> translate(const std::vector<Point2D> & points, int tx, int ty);

	Point2D rotate(const Point2D & point, int xr, int yr, double theta);
	std::vector<Point2D> rotate(const std::vector<Point2D> & points, int xr, int yr, double theta);

	std::vector<Point2D> scale(const std::vector<Point2D> & points, int xf, int yf, double sx, double sy);

}
