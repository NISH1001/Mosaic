#pragma once

#include <iostream>
#include <Vector.h>

/*
------------------- A 2D point struct ---------------------------
*/

struct Point2D
{
	struct { int x, y; }; // for contagious storage in memory
	float depth;
	Vec3 attributes[2]; // point has only one attribute now, that is color,normal

	Point2D(int xx, int yy) : x(xx) , y(yy) {depth=0;} // initially set the depth value to be 0
	Point2D() {} 
//	~Point2D(void) {}

	bool operator==(const Point2D & point);
	bool operator>(const Point2D & point);
	bool operator<(const Point2D & point);
	Point2D operator+(const Point2D & point);
	Point2D operator-(const Point2D & point);
};


/*a 3D vertex struct
	a vertex has its positionition
	a color attribute
	a normal attribute
*/

struct Vertex3D
{
	Vec4 position; // the x,y,z coordinates
	Vec3 normal; // for normal
	Vec3 color; // for the color

	Vertex3D () {}
	Vertex3D(const Vec4 & p, const Vec3 & n, const Vec3 & c) : position(p), normal(n), color(c) {}

	bool operator == (const Vertex3D & v)
	{
		return (position.x==v.position.x && position.y==v.position.y && position.z==v.position.z);
	}
};

inline std::ostream& operator << (std::ostream & os, const Vertex3D & v)
{
	os<< v.position.x << " " << v.position.y << " " << v.position.z;
	return os;
}
