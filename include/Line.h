#pragma once

#include <Point2D.h>
#include <pixel.h>

struct Line
{
public:
	Line(int xstart, int ystart, int xend, int yend);
	Line(const Point2D & start, const Point2D & end);
	bool nextPoint(void);
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