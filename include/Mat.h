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

	// return 4x4 identity matrix
	static Matrix Mat4(void);	

	//return 3x1 homogeneous matrix for given 2D point
	static Matrix Vec2(double x, double y);
	static Matrix Vec2(const Point2D & p);

	//return 4x1 homogeneous matrix for given 3D point
	static Matrix Vec3(double x, double y,double z);
private:

};
