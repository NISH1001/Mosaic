#pragma once
#include <pixel.h>
#include <Line.h>
#include <Point2D.h>
#include <vector>

namespace Transform
{
	/* general transformation function
		accepts transformation matrix mat
		and a point
	*/
	Point2D transform(double (*mat)[3], const Point2D & point);

	/*either translate a point or a set of points 
	 	in fututre the set of points can be an object type
	*/
	Point2D translate(Point2D & point, double tx, double ty);
	std::vector<Point2D> translate(const std::vector<Point2D> & points, double tx, double ty);

	/*rotate a point/points about a point*/
	Point2D rotate(const Point2D & point, int xr, int yr, double theta);
	std::vector<Point2D> rotate(const std::vector<Point2D> & points, int xr, int yr, double theta);

	/*general scaling
	scaling only in parallel x/y direction*/
	std::vector<Point2D> scale(const std::vector<Point2D> & points, int xf, int yf, double sx, double sy);

	// scaling a point
	Point2D scale(const Point2D & point, double xf, double yf, double sx, double sy);

	// reflection
	Point2D reflect(const Point2D &point, double m, double c);

}
