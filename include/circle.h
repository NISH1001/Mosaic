#ifndef CIRCLE_H
#define CIRCLE_H

#include "pixel.h"
#include "bresenham.h"



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
