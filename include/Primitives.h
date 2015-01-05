#pragma once
#include <pixel.h>
#include <Line.h>
#include <algorithm>

namespace Primitives
{

	void ellipsePlot(SDL_Renderer*renderer, int cx, int cy, int x, int y, ColorRGBA color);

	void ellipseFill(SDL_Renderer *renderer, int cx, int cy, int rx, int ry, ColorRGBA color);

	void ellipse(SDL_Renderer *renderer, int cx, int cy, int rx, int ry, ColorRGBA color);
	
	void bresenham(SDL_Renderer *renderer, int xstart, int ystart, int xend, int yend, ColorRGBA color);
	void bresenham(SDL_Renderer *renderer, const Point2D & start, const Point2D & end, ColorRGBA color);

	void circlePlot(SDL_Renderer *renderer, int cx, int cy, int x, int y, ColorRGBA color);
	
	void circleFill(SDL_Renderer *renderer, int cx, int cy, int r, ColorRGBA color);
	
	void circle(SDL_Renderer *renderer, int cx, int cy, int r, ColorRGBA color);

	void triangleFill(SDL_Renderer *renderer, int x1, int y1, int x2 ,int y2, int x3, int y3, ColorRGBA color);
	void triangleFill(SDL_Renderer *renderer, Point2D p1, Point2D p2, Point2D p3, ColorRGBA color);
	void triangle(SDL_Renderer *renderer, int x1, int y1, int x2 ,int y2, int x3, int y3, ColorRGBA color);
	void triangle(SDL_Renderer *renderer, Point2D p1, Point2D p2, Point2D p3, ColorRGBA color);
	namespace TriangleHelper
	{
		void triangleFlatFill(SDL_Renderer *renderer, int xt, int yt, int xb1, int xb2, int yb, ColorRGBA color);
		void sortY(int & x1, int & y1, int & x2, int & y2, int & x3, int & y3) ;
	}

	namespace PolygonHelper
	{
		double cross(const Point2D & O, const Point2D & A, const Point2D & B);
		std::vector<Point2D> convexHull(std::vector<Point2D> P);
	}
	void polygonFill(SDL_Renderer *renderer, const std::vector<Point2D> & points, ColorRGBA color);
	void polygon(SDL_Renderer *renderer, const std::vector<Point2D> & points, ColorRGBA color);
}
