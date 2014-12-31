#ifndef CIRCLE_H
#define CIRCLE_H

#include "pixel.h"
#include "bresenham.h"

void circlePlot(SDL_Renderer *renderer, int cx, int cy, int x, int y, ColorRGBA color)
{
    setPixel(renderer, cx+x, cy+y, color);
    
    setPixel(renderer, cx-x, cy+y, color);

    setPixel(renderer, cx+x, cy-y, color);
    
    setPixel(renderer, cx-x, cy-y, color);

    setPixel(renderer, cx+y, cy+x, color);

    setPixel(renderer, cx-y, cy+x, color);

    setPixel(renderer, cx+y, cy-x, color);

    setPixel(renderer, cx-y, cy-x, color);
}

void circleFill(SDL_Renderer *renderer, int cx, int cy, int r, ColorRGBA color)

{
    int x = 0;
    int y = r;
    int p = 1-r;;

    circlePlot(renderer, cx, cy, x, y, color);
    bresenham(renderer, cx+x, cy+y, cx+x,cy-y, color);

    while(x <= y)
    {
        x++;

        if(p<0)
            p += 2*x+1;

        else
        {
            y--;
            p += 2*(x-y)+1;
        }

        circlePlot(renderer, cx, cy, x, y, color);

        bresenham(renderer, cx+x, cy+y, cx+x, cy-y, color);
        bresenham(renderer, cx+y, cy+x, cx+y, cy-x, color);
        bresenham(renderer, cx-x, cy+y, cx-x, cy-y, color);
        bresenham(renderer, cx-y, cy+x, cx-y, cy-x, color);
    }
}

void Circle(SDL_Renderer *renderer, int cx, int cy, int r, ColorRGBA color)
{
    int x = 0;
    int y = r;
    int p = 1-r;
    
    circlePlot(renderer, cx, cy, x, y, color);
    
    while(x<=y)
    {
        x++;
        
        if(p<0)
            p += 2*x+1;

        else
        {
            y--;
            p += 2*(x-y)+1; 
        }   
        
        circlePlot(renderer, cx, cy, x, y, color);
    }       
}

#endif //CIRCLE_H