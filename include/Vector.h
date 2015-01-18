#pragma once

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

private:
};

class Vec4
{
public:
	struct{float x, y, z, w;}; // used struct so that x,y,z,w are contagious in memory

	Vec4(void) : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {} 
	Vec4(float xx, float yy, float zz, float ww) : x(xx), y(yy), z(zz), w(ww) {}

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

private:
};

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