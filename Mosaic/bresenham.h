#ifndef BRESENHAM_H
#define BRESENHAM_H

#include "pixel.h"

void bresenham(SDL_Renderer *renderer, int xstart, int ystart, int xend, int yend, ColorRGBA color)
{
	int dx = abs(xend - xstart);
	int dy = abs(yend - ystart);
	
	int xinc = (xend>xstart ? 1 : -1);
	int yinc = (yend>ystart ? 1 : -1);	
	
	int twodx = 2*dx;
	int twody = 2*dy;
	int twodydx = twody - twodx;
	int x = xstart;
	int y = ystart;	
		
	setPixel(renderer, xstart, ystart, color);
	
	if(dx > dy)
	{
		int p = twody - dx;
		
		while(x != xend)
		{
			x += xinc;
		
			if(p<0)
			{
				p += twody;	
			}
			else
			{	
				y += yinc;
				p += twodydx;
			}
			setPixel(renderer, x , y, color);
		}
	}
	
	else
	{
		int p = twodx - dy;
		
		while(y != yend)
		{
			y += yinc;
			if(p <0)
			{	p += twodx;
			}
			else
			{
				x += xinc;
				p -= twodydx;
			}
			setPixel(renderer, x, y, color);
		}

	}
}

#endif //BRESENHAM_H
