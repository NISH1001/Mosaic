#pragma once

#include <Point2D.h>
#include <Primitive.h>

/*
	Line object used for polygon filling
	As we can plot the scanline horizontally
	using two interseting lines
*/


class Line : public Primitive
{
public:
	Line(SDL_Renderer * renderer,int xstart, int ystart, int xend, int yend, ColorRGBA color);
	Line(SDL_Renderer* Renderer,const Point2D & start, const Point2D & end, ColorRGBA color);
	Line(int xstart, int ystart, int xend, int yend);
	Line(const Point2D & start, const Point2D & end);

	/*check to see if next point is available one the line
		Also calculates next point and stores as current one
		If end point is reached, then no nextpoint is available
	*/
	bool NextPoint(void);
	virtual void Draw();
	virtual void DrawFilled();


public:
	Point2D m_currentPoint;
private:
	SDL_Renderer * m_renderer;
	ColorRGBA m_color;
	Point2D m_endPoint;
	bool  slope_less_one;
	int xinc, yinc, dx, dy;
	int twodx, twody;
	int twodydx;
	int p;
};
