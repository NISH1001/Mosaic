#pragma once

#include <Matrix.h>
#include <Point2D.h>

/*
	Uses Matrix class
*/

class Mat
{
public:
	// return 3x3 identity
	static Matrix Mat3(void);
	static Matrix Mat3(double);

	//return 3x3 matrix with all elements
	static Matrix Mat3(double x);

	// return 4x4 identity matrix
	static Matrix Mat4(void);
	//return 4x4 matrix with all elements
	static Matrix Mat4(double x);	

	//return 2x1 matrix for given 2D point
	static Matrix Vec2(double x, double y);
	static Matrix Vec2(const Point2D & p);

	//return 3x1 matrix for given 3D point
	static Matrix Vec3(double x, double y,double z);
	static Matrix Vec3(const Matrix & vec2, double z);

	//return 4x1 matrix
	static Matrix Vec4(double x, double y, double z, double w);
	static Matrix Vec4(const Matrix & vec3, double w);

private:

};
