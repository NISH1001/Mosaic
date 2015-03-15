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

	static Mat4 Rotate(float angle, const Vec3& vec, const Vec3 & point)
	{
		angle = M_PI * angle/180;
		Vec3 axis = vec;
		axis.NormalizeToUnit();

		float sine = sinf(angle);
		float cosine = cosf(angle);

		float u = axis.x, v = axis.y, w = axis.z;
		float a = point.x, b = point.y, c = point.z;

		 return Mat4(
					u*u+(v*v+w*w)*cosine, u*v*(1-cosine)-w*sine, u*w*(1-cosine)+v*sine, (a*(v*v+w*w)-u*(b*v+c*w))*(1-cosine)+(b*w-c*v)*sine,
					u*v*(1-cosine)+w*sine, v*v+(u*u+w*w)*cosine, v*w*(1-cosine)-u*sine, (b*(u*u+w*w)-v*(a*u+c*w))*(1-cosine)+(c*u-a*w)*sine,
					u*w*(1-cosine)-v*sine, v*w*(1-cosine)+u*sine, w*w+(u*u+v*v)*cosine, (c*(u*u+v*v)-w*(a*u+b*v))*(1-cosine)+(a*v-b*u)*sine,
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

    static Mat4 Scale(float sx, float sy, float sz)
    {
        return Mat4(
                sx, 0, 0, 0,
                0, sy, 0, 0,
                0, 0, sz, 0,
                0, 0, 0, 1
                );
    }

    static Mat4 Scale(const Vec3 & sc)
    {
        return Scale(sc.x, sc.y, sc.z);
    }

	static Mat4 Perspective(float fieldView, float aspectRatio, float near, float far)
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

    static Mat4 Orthographic(float left, float right, float bottom, float top, float near, float far)
    {
        float rl = 1.0f/(right - left);
        float tb = 1.0f/(top - bottom);
        float fn = 1.0f/(far - near);
        return Mat4(
                2*rl, 0, 0, -(right+left)*rl,
                0, 2*tb, 0, -(top+bottom)*tb,
                0, 0, -2*fn, -(far+near)*fn,
                0, 0, 0, 1
                );
    }


	// LookAt returns model view matrix
	static Mat4 LookAt(Vec3 from, Vec3 to) 
	{
		// first set up the translate matrix
		Mat4 translate = Translate(from * (-1)); // negative of looking point

		Vec3 v(0,1,0); // initially V is upwards
		Vec3 n = from - to;
		n.NormalizeToUnit();
		
		Vec3 crossvn = Vec3::Cross(v,n);
		crossvn.NormalizeToUnit();
		//crossvn = Vec3::NormalizeToUnit(crossvn);

		Vec3 u = crossvn;
		
		v= Vec3::Cross(n,u);

		Mat4 rotate = Mat4(Vec4(u,0), Vec4(v,0), Vec4(n,0), Vec4(0,0,0,1)); 
		/*Mat4 rotate = Mat4(u[0],v[0],n[0],0,
				u[1],v[1],n[1],0,
				u[2],v[2],n[2],0,
				0,0,0,1); */
		return rotate * translate;
	}


private:
	//Transform(){}
};
