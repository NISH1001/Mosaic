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
	Vec3 attributes[1]; // point has only one attribute now, that is normal

	Point2D(int xx, int yy) : x(xx) , y(yy) {depth=0;} // initially set the depth value to be 0
	Point2D() {} 
//	~Point2D(void) {}

	bool operator==(const Point2D & point);
	bool operator>(const Point2D & point);
	bool operator<(const Point2D & point);
	Point2D operator+(const Point2D & point);
	Point2D operator-(const Point2D & point);
};

