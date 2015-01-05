#include <Transform.h>

Point2D Transform::transform(double (*mat)[3], const Point2D & point)
{
	Point2D res = point;

	res.x = mat[0][0]*point.x + mat[0][1]*point.y + mat[0][2];
	res.y = mat[1][0]*point.x + mat[1][1]*point.y + mat[1][2];

	return res;
}

Point2D Transform::translate(const Point2D & point, int tx, int ty)
{
	double mat[3][3] = {{1,0,tx}, 
						{0,1,ty}, 
						{0,0,1}};
	return transform(mat, point);
}

std::vector<Point2D> Transform::translate(const std::vector<Point2D> & points, int tx, int ty)
{
	std::vector<Point2D> res;
	res.resize(points.size());
	double mat[3][3] = {{1,0,tx}, 
						{0,1,ty}, 
						{0,0,1}};

	for(int i=0; i<points.size(); i++)
	{
		res[i] = transform(mat, points[i]);
	}
	return res;
}

Point2D Transform::rotate(const Point2D & point, int xr, int yr, double theta)
{
	theta = -M_PI * theta / 180;
	double mat[3][3] = {{cos(theta), -sin(theta), xr*(1-cos(theta)) + yr*sin(theta) }, 
						{sin(theta), cos(theta), yr*(1-cos(theta)) - xr*sin(theta)}, 
						{0, 		0, 			1}};
	return transform(mat, point);
}

std::vector<Point2D> Transform::rotate(const std::vector<Point2D> & points, int xr, int yr, double theta)
{
	std::vector<Point2D> res;
	res.resize(points.size());
	theta = -M_PI * theta / 180;
	double mat[3][3] = {{cos(theta), -sin(theta), xr*(1-cos(theta)) + yr*sin(theta) }, 
						{sin(theta), cos(theta), yr*(1-cos(theta)) - xr*sin(theta)}, 
						{0, 		0, 			1}};

	for(int i=0; i<points.size(); i++)
	{
		res[i] = transform(mat, points[i]);
	}
	return res;
}

std::vector<Point2D> Transform::scale(const std::vector<Point2D> & points, int xf, int yf, double sx, double sy)
{
	std::vector<Point2D> res;
	res.resize(points.size());

	double mat[3][3] = {{sx, 0, xf*(1-sx) }, 
						{0, sy, yf*(1-sy) }, 
						{0, 0, 1}	};

	for(int i=0; i<points.size(); i++)
	{
		res[i] = transform(mat, points[i]);
	}
	return res;
}