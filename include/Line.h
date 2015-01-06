#pragma once

#include <Point2D.h>
#include <pixel.h>

/*
	Line object used for polygon filling
	As we can plot the scanline horizontally
	using two interseting lines
*/
struct Line
{
public:
	Line(int xstart, int ystart, int xend, int yend);
	Line(const Point2D & start, const Point2D & end);

	/*check to see if next point is available one the line
		Also calculates next point and stores as current one
		If end point is reached, then no nextpoint is available
	*/
	bool nextPoint(void);

	/*draw the whole line start to end*/
	void draw(SDL_Renderer *renderer, ColorRGBA color);

public:
	Point2D m_currentPoint;
private:
	Point2D m_endPoint;
	bool  slope_less_one;
	int xinc, yinc;
	int twodx, twody;
	int twodydx;
	int p;
};