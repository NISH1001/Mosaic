#pragma once

#include <Matrix.h>
#include <Vector.h>
#include <cmath>

class Transform
{
public:
	static Mat4 Translate(const Vec3 & vec)
	{
		return Mat4(
					1, 0, 0, vec.x,
					0, 1, 0, vec.y,
					0, 0, 1, vec.z,
					0, 0, 0, 1
					);
	}

	static Mat4 Translate(float tx, float ty, float tz)
	{
		return Mat4(
					1, 0, 0, tx,
					0, 1, 0, ty,
					0, 0, 1, tz,
					0, 0, 0, 1
					);	
	}

	static Mat4 RotateX(float angle)
	{
		angle = M_PI * angle/180;
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
		angle = M_PI * angle/180;
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
		angle = M_PI * angle/180;
		float a=cosf(angle),b=sinf(angle);

		return Mat4(
					a, -b, 0, 0,
					b, a, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1
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

	static Mat4 GetPerspective(float fieldView, float aspectRatio, float near, float far)
	{
		float cot = 1.f/tanf(fieldView/2.f);
		float invAR = 1.f/aspectRatio;
		float nMinusF = near-far,nPlusf = near+far;
		return Mat4(invAR*cot, 0, 0, 0,
				0, cot, 0, 0,
				0, 0, nPlusf/nMinusF, 2*far*near/nMinusF,
				0,0, -1, 0
				);
	}


	// LookAt returns model view matrix
	static Mat4 LookAt(Vec3 from, Vec3 to) 
	{
		// first set up the translate matrix
		Mat4 translate = Translate(from * (-1)); // negative of looking point

		Vec3 v(0,1,0); // initially V is upwards
		Vec3 N = from - to;
		Vec3 n = GetUnitVector(N);
		Vec3 crossVN = GetCrossProduct(v, n);
		Vec3 u = GetUnitVector(crossVN);
		v = GetCrossProduct(n, u);

		Mat4 rotate = Mat4(Vec4(u,0), Vec4(v,0), Vec4(n,0), Vec4(0,0,0,1)); 
		return rotate* translate;
	}


private:
	//Transform(){}
};
