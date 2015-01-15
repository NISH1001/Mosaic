#pragma once

class Vec3
{
public:
	 struct { float x, y, z; };

	Vec3(void)  : x(0.0f), y(0.0f), z(0.0f) {}
	Vec3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

	Vec3 operator + (const Vec3 & other) const
	{
		return Vec3(x+other.x, y+other.y, z+other.z);
	}

	Vec3 operator - (const Vec3 & other)
	{
		return Vec3(x-other.x, y-other.y, z-otherz);
	}

	Vec3 operator * (float k) const 
	{
		return Vec3(k*x, k*y, k*z);
	}

	Vec3 operator / (float k) const
	{
		return Vec3(x/k, y/k, z/k);
	}

	float operator[] (size_t i) const
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
	struct{float x, float y, float z, float w};

	Vec4(void) : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {} 
	Vec4(float xx, float yy, float zz, float ww) : x(xx), y(yy), z(zz), w(ww) {}

	Vec4(const Vec3& v2) : x(v.x), y(v.y), z(v.z) , w(1.0f) {}

	Vec4 operator + (const Vec4 & other) const
	{
		return Vec4(x+other.x, y+other.y, z+other.z, w+oter.w);
	}

	Vec4 operator - (const Vec4 & other) const
	{
		return Vec4(x-other.x, y-other.y, z-other.z, w-oter.w);
	}

	Vec4 operator * (float k) const 
	{
		return Vec4(k*x, k*y, k*z, k*w);
	}

	Vec4 operator / (float k) const 
	{
		return Vec4(x/k, y/k, z/k, w/k);
	}

	float operator[] (size_t i) const
	{
		if(i>=4)
		{
			throw "index access error...";
		}
		return (&x)[i];
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