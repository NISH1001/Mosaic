#pragma once

#include <iostream>

struct Point2D
{
	int x;
	int y;

	Point2D(int xx, int yy) : x(xx) , y(yy) {}
	Point2D() {} 
//	~Point2D(void) {}

	bool operator==(const Point2D & point);
	bool operator>(const Point2D & point);
	bool operator<(const Point2D & point);
	Point2D operator+(const Point2D & point);
	Point2D operator-(const Point2D & point);
};