#pragma once
#include <cmath>

//#include <cstddef>
#include <iostream>
/*
	Vector classes : 3D vector and 4D vector
*/

class Vec3
{
public:
	 struct { float x, y, z; }; // used struct, so that x,y,z are contagious 

	//default -> all 0
	Vec3(void)  : x(0.0f), y(0.0f), z(0.0f) {}

	// use 3 elements to init
	Vec3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

	Vec3 operator + (const Vec3 & other) const
	{
		return Vec3(x+other.x, y+other.y, z+other.z);
	}

	Vec3 operator - (const Vec3 & other)
	{
		return Vec3(x-other.x, y-other.y, z-other.z);
	}

	void operator-=(const Vec3 & other)
	{
		x = x-other.x; y=y-other.y; z=z-other.z;
	}

	void operator+=(const Vec3 & other)
	{
		x = x+other.x; y=y+other.y; z=z+other.z;
	}

	Vec3 operator * (float k) const 
	{
		return Vec3(k*x, k*y, k*z);
	}

	Vec3 operator / (float k) const
	{
		return Vec3(x/k, y/k, z/k);
	}

	float  operator[] (size_t i) const
	{
		if(i>=3)
		{
			throw "index access error...";
		}
		return (&x)[i];
	}

	float & operator[] (size_t i)
	{
		if(i>=3)
		{
			throw "index access error...";
		}
		return (&x)[i];
	}

	static float Dot(Vec3& v1, Vec3& v2)
	{
		return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}

	static Vec3 Cross(Vec3& a, Vec3& b)
	{
		return Vec3(
				a.y * b.z - b.y * a.z,
				a.z * b.x - b.z * b.x,
				a.x * b.y - b.x * a.y
				);
	}

private:
};

class Vec4
{
public:
	struct{float x, y, z, w;}; // used struct so that x,y,z,w are contagious in memory

	Vec4(void) : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {} 
	Vec4(float xx, float yy, float zz, float ww=1.f) : x(xx), y(yy), z(zz), w(ww) {}

	//use 3D vector and another element to init
	Vec4(const Vec3& v, float ww=1.0f) : x(v.x), y(v.y), z(v.z) , w(ww) {}

	Vec4 operator + (const Vec4 & other) const
	{
		return Vec4(x+other.x, y+other.y, z+other.z, w+other.w);
	}

	Vec4 operator - (const Vec4 & other) const
	{
		return Vec4(x-other.x, y-other.y, z-other.z, w-other.w);
	}

	Vec4 operator * (float k) const 
	{
		return Vec4(k*x, k*y, k*z, k*w);
	}

	Vec4 operator / (float k) const 
	{
		return Vec4(x/k, y/k, z/k, w/k);
	}

	float  operator[] (size_t i) const
	{
		if(i>=4)
		{
			throw "index access error...";
		}
		return (&x)[i];
	}

	float & operator[] (size_t i)
	{
		if(i>=4)
		{
			throw "index access error...";
		}
		return (&x)[i];
	}

	void NormalizeByW(void)
	{
		if(w!=1 && w!=0)
		{
			x = x/w;
			y = y/w;
			z = z/w;
			w = 1;
		}
	}

	Vec3 ToVec3()
	{
		NormalizeByW();
		return Vec3(x, y, z);
	}

private:
};

// vector helper functions
inline Vec3 GetUnitVector(const Vec3 & mat)
{
	float r = sqrtf(mat.x*mat.x + mat.y*mat.y + mat.z*mat.z);
	return mat/r;
}

inline Vec3 GetCrossProduct(const Vec3 & a, const Vec3 &b)
{
	return Vec3(
				a.y * b.z - b.y * a.z,
				a.z * b.x - b.z * b.x,
				a.x * b.y - b.x * a.y
				);
}



inline std::ostream& operator << (std::ostream &os, const Vec3 &v3)
{
	os << v3.x << " " << v3.y << " " << v3.z;
	return os;
}

inline std::ostream& operator << (std::ostream &os, const Vec4 &v4)
{
	os << v4.x << " " << v4.y << " " << v4.z << " " << v4.w;
	return os;
}
