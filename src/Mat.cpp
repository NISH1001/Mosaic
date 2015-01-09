#include <Mat.h>

Matrix Mat::Mat3()
{
	Matrix mat(3,3);
	mat[0][0] = 1;
	mat[1][1] = 1;
	mat[2][2] = 1;
	return mat;
}

Matrix Mat::Mat3(double x)
{
	Matrix mat(3,3);
	mat[0][0] = mat[1][1] = mat[2][2] = x;
	return mat;
}

Matrix Mat::Mat4()
{
	Matrix mat(4,4);
	mat[0][0] = 1;
	mat[1][1] = 1;
	mat[2][2] = 1;
	mat[3][3] = 1;
	return mat;
}

Matrix Mat::Vec2(double x, double y)
{
	Matrix mat31(3,1);
	mat31[0][0] = x;
	mat31[1][0] = y;
	mat31[2][0] = 1;
	return mat31;
}

Matrix Mat::Vec2(const Point2D & p)
{
	Matrix mat31(3,1);
	mat31[0][0] = p.x;
	mat31[1][0] = p.y;
	mat31[2][0] = 1;
	return mat31;
}

Matrix Mat::Vec3(double x, double y,double z)
{
	Matrix mat41(4,1);
	mat41[0][0] = x;
	mat41[1][0] = y;
	mat41[2][0] = z;
	mat41[3][0] = 1;
	return mat41;
}
