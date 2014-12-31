#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "pixel.h"

void ellipsePlot(SDL_Renderer *renderer, int cx, int cy, int x, int y, ColorRGBA color)
{
	setPixel(renderer, cx+x, cy+y, color);
	setPixel(renderer, cx-x, cy+y, color);
	setPixel(renderer, cx+x, cy-y, color);
	setPixel(renderer, cx-x, cy-y, color);
}

void ellipseFill(SDL_Renderer *renderer, int cx, int cy, int rx, int ry, ColorRGBA color)
{
	int rx2 = rx * rx;
	int ry2 = ry * ry;
	int tworx2 = 2 * rx2;
	int twory2 = 2 * ry2;
	
	int x = 0;
	int y = ry;

	int p = ry2 - rx2*ry + rx2/4;
	
	ellipsePlot(renderer, cx, cy, x, y, color);
	
	while(x*ry2 < y*rx2)
	{
		x++;
		
		if(p<0)
			p += x*twory2 + ry2;
		
		else
		{
			y--;
			p += x*twory2 + ry2 - y*tworx2;
		}
		
		ellipsePlot(renderer, cx, cy , x, y, color);

        bresenham(renderer, cx+x, cy-y, cx-x, cy-y, color);
        bresenham(renderer, cx+x, cy+y, cx-x, cy+y, color);
	}

	p = ry2*(x+0.5)*(x+0.5) + rx2*(y-1)*(y-1) - rx2*ry2;
	
	while(y>=0)
	{
		y--;
		
		if(p<0)
		{
			x++;
			p += x*twory2-y*tworx2 + 3*rx2;
		}
		
		else
			p += 3*rx2-y*tworx2;
		
		ellipsePlot(renderer, cx, cy , x, y, color);
        
        bresenham(renderer, cx+x, cy-y, cx-x, cy-y, color);
        bresenham(renderer, cx+x, cy+y, cx-x, cy+y, color);
	}
}

void ellipse(SDL_Renderer *renderer, int cx, int cy, int rx, int ry, ColorRGBA color)
{
	int rx2 = rx * rx;
	int ry2 = ry * ry;
	int tworx2 = 2 * rx2;
	int twory2 = 2 * ry2;
	
	int x = 0;
	int y = ry;

	int p = ry2 - rx2*ry + rx2/4;
	
	ellipsePlot(renderer, cx, cy, x, y, color);
	
	while(x*ry2 < y*rx2)
	{
		x++;
		
		if(p<0)
			p += x*twory2 + ry2;
		
		else
		{
			y--;
			p += x*twory2 + ry2 - y*tworx2;
		}
		
		ellipsePlot(renderer, cx, cy , x, y, color);
	}

	p = ry2*(x+0.5)*(x+0.5) + rx2*(y-1)*(y-1) - rx2*ry2;
	
	while(y>=0)
	{
		y--;
		
		if(p<0)
		{
			x++;
			p += x*twory2-y*tworx2 + 3*rx2;
		}
		
		else
			p += 3*rx2-y*tworx2;
		
		ellipsePlot(renderer, cx, cy , x, y, color);
	}
}

#endif //ELLIPSE_H