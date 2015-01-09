#include <Mat.h>

Matrix Mat::Mat3(void)
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
	mat[0][0] = x;
	mat[0][1] = x;
	mat[0][2] = x;
	mat[1][0] = x;
	mat[1][1] = x;
	mat[1][2] = x;
	mat[2][0] = x;
	mat[2][1] = x;
	mat[2][2] = x;
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

Matrix Mat::Mat4(double x)
{
	Matrix mat(4,4);
	mat[0][0] = x;
	mat[0][1] = x;
	mat[0][2] = x;
	mat[1][0] = x;
	mat[1][1] = x;
	mat[1][2] = x;
	mat[2][0] = x;
	mat[2][1] = x;
	mat[2][2] = x;
	mat[3][0] = x;
	mat[3][1] = x;
	mat[3][2] = x;
	return mat;
}

Matrix Mat::Vec2(double x, double y)
{
	Matrix mat21(2,1);
	mat21[0][0] = x;
	mat21[1][0] = y;
	//mat21[2][0] = 1;
	return mat21;
}

Matrix Mat::Vec2(const Point2D & p)
{
	Matrix mat21(2,1);
	mat21[0][0] = p.x;
	mat21[1][0] = p.y;
	//mat21[2][0] = 1;
	return mat21;
}

Matrix Mat::Vec3(double x, double y,double z)
{
	Matrix mat31(3,1);
	mat31[0][0] = x;
	mat31[1][0] = y;
	mat31[2][0] = z;
	//mat31[3][0] = 1;
	return mat31;
}

Matrix Mat::Vec3(const Matrix & vec2, double z)
{
	Matrix mat31(3,1);
	mat31[0][0] = vec2[0][0];
	mat31[1][0] = vec2[1][0];
	mat31[2][0] = z;
	//mat31[3][0] = 1;
	return mat31;
}

Matrix Mat::Vec4(double x, double y, double z, double w)
{
	Matrix mat41(4,1);
	mat41[0][0] = x;
	mat41[1][0] = y;
	mat41[2][0] = z;
	mat41[3][0] = w;
	return mat41;
}

Matrix Mat::Vec4(const Matrix & vec3, double w)
{
	Matrix mat41(4,1);
	mat41[0][0] = vec3[0][0];
	mat41[1][0] = vec3[1][0];
	mat41[2][0] = vec3[2][0];
	mat41[3][0] = w;
	return mat41;
}