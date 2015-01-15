#pragma once

#include <Matrix.h>
#include <cmath>

class Transform
{
public:
	static Mat4 Translate(const Vec3 & vec)
	{
		return Mat4(
					1.0f, 0.0f, 0.0f, vec.x,
					0.0f, 1.0f, 0.0f, vec.y,
					0.0f, 0.0f, 1.0f, vec.z,
					0.0f, 0.0f, 0.0f, 1
					);
	}

	static Mat4 Translate(float tx, float ty, float tz)
	{
		return Mat4(
					1.0f, 0.0f, 0.0f, tx,
					0.0f, 1.0f, 0.0f, ty,
					0.0f, 0.0f, 1.0f, tz,
					0.0f, 0.0f, 0.0f, 1
					);	
	}

	static Mat4 RotateX(float angle)
	{
		angle = 3.14 * angle/180;
		float a=cosf(angle),b=sinf(angle);

		return Mat4(
					1, 0, 0, 0, 
					0, a, -b, 0,
					0, b, a, 0,
					0, 0, 0, 1
					);
	}

	static Mat4 RotateY(float angle)
	{
		float a=cosf(angle),b=sinf(angle);

		return Mat4(
					a, 0, b, 0,
					0, 1, 0, 0,
					-b, 0, a, 0,
					0, 0, 0, 1
					);
	}

	static Mat4 RotateZ(float angle)
	{
		float a=cosf(angle),b=sinf(angle);

		return Mat4(
					a, -b, 0, 0,
					b, a, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 01
					);	
	}

	static Mat4 Scale(const Vec3& sc, const Vec3& vec)
	{
		return Mat4(
					sc.x, 0, 0, (1-sc.x)*vec.x,
					0, sc.y, 0, (1-sc.y)*vec.y,
					0, 0, sc.z, (1-sc.z)*vec.z,
					0, 0, 0, 1
					);
	}


private:
	Transform(){}
};