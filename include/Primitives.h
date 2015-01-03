#pragma once
#include <pixel.h>
#include <Line.h>

namespace Primitives
{

	void ellipsePlot(SDL_Renderer*renderer, int cx, int cy, int x, int y, ColorRGBA color);

	void ellipseFill(SDL_Renderer *renderer, int cx, int cy, int rx, int ry, ColorRGBA color);

	void ellipse(SDL_Renderer *renderer, int cx, int cy, int rx, int ry, ColorRGBA color);
	
	void bresenham(SDL_Renderer *renderer, int xstart, int ystart, int xend, int yend, ColorRGBA color);

	void circlePlot(SDL_Renderer *renderer, int cx, int cy, int x, int y, ColorRGBA color);
	
	void circleFill(SDL_Renderer *renderer, int cx, int cy, int r, ColorRGBA color);
	
	void circle(SDL_Renderer *renderer, int cx, int cy, int r, ColorRGBA color);

	void triangleFlatFill(SDL_Renderer *renderer, int xt, int yt, int xb1, int xb2, int yb, ColorRGBA color);
}
