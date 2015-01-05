#include <Primitives.h>

void Primitives::ellipsePlot(SDL_Renderer *renderer, int cx, int cy, int x, int y, ColorRGBA color)
{
	setPixel(renderer, cx+x, cy+y, color);
	setPixel(renderer, cx-x, cy+y, color);
	setPixel(renderer, cx+x, cy-y, color);
	setPixel(renderer, cx-x, cy-y, color);
}

void Primitives::ellipseFill(SDL_Renderer *renderer, int cx, int cy, int rx, int ry, ColorRGBA color)
{
	int rx2 = rx * rx;
	int ry2 = ry * ry;
	int tworx2 = 2 * rx2;
	int twory2 = 2 * ry2;
	
	int x = 0;
	int y = ry;

	int p = ry2 - rx2*ry + rx2/4.f + 0.5f;
	
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

void Primitives::ellipse(SDL_Renderer *renderer, int cx, int cy, int rx, int ry, ColorRGBA color)
{
	int rx2 = rx * rx;
	int ry2 = ry * ry;
	int tworx2 = 2 * rx2;
	int twory2 = 2 * ry2;
	
	int x = 0;
	int y = ry;

	int p = ry2 - rx2*ry + rx2/4.f + 0.5f;
	
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

void Primitives::bresenham(SDL_Renderer *renderer, int xstart, int ystart, int xend, int yend, ColorRGBA color)
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
				p += twodx;
			else
			{
				x += xinc;
				p -= twodydx;
			}
			setPixel(renderer, x, y, color);
		}

	}
}

void Primitives::bresenham(SDL_Renderer *renderer, const Point2D & start, const Point2D & end, ColorRGBA color)
{
	bresenham(renderer, start.x, start.y, end.x, end.y, color);
}


void Primitives::circlePlot(SDL_Renderer *renderer, int cx, int cy, int x, int y, ColorRGBA color)
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

void Primitives::circleFill(SDL_Renderer *renderer, int cx, int cy, int r, ColorRGBA color)

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

void Primitives::circle(SDL_Renderer *renderer, int cx, int cy, int r, ColorRGBA color)
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


/*---------------------------- TRIANGLE------------------*/

/* sort the point according to y */
void Primitives::TriangleHelper::sortY(int & x1, int & y1, int & x2, int & y2, int & x3, int & y3) 
{
	if (y1 > y2) 
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	if (y2 > y3) 
	{
		std::swap(x2, x3);
		std::swap(y2, y3);
	} ///largest yvalue coord is at 3
	if (y1 > y2) 
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
}

/* just a triangle with a horizontal side */
void Primitives::TriangleHelper::triangleFlatFill(SDL_Renderer *renderer, int xt, int yt, 
										int xb1, int xb2, int yb, ColorRGBA color)
{
	if(yt == yb) return;
	
	Line line1(xt, yt, xb1, yb);
	line1.nextPoint();
	Line line2(xt, yt, xb2, yb);
	line2.nextPoint();
	
	while(1)
	{
		if((line1.m_currentPoint.x == xb1) &&  (line2.m_currentPoint.x==xb2))
			break;

		while(line1.m_currentPoint.y != line2.m_currentPoint.y)
		{
			if(!line1.nextPoint())
				break;
		}
		Line scanline(line1.m_currentPoint.x, line1.m_currentPoint.y, line2.m_currentPoint.x, line2.m_currentPoint.y);
		scanline.draw(renderer, color);

		if(!line2.nextPoint()) break;
	}
}

/* real public function */
void Primitives::triangleFill(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int x3, int y3, ColorRGBA color)
{
    TriangleHelper::sortY(x1, y1, x2, y2, x3, y3);

    if(y2 == y3)
    {
    	TriangleHelper::triangleFlatFill(renderer, x1, y1, x2, x3, y2, color);
    }

    else if(y1 == y2)
    {
    	TriangleHelper::triangleFlatFill(renderer, x3, y3, x1, x2, y1, color);
    }

    else
    {
    	int x4 = x1 == x3 ? x1 : (x1 + (int)((y2 - y1) * 1.0 * (x3 - x1) / (y3 - y1)));
    	TriangleHelper::triangleFlatFill(renderer, x1, y1, x2, x4, y2, color);
		TriangleHelper::triangleFlatFill(renderer, x3, y3, x2, x4, y2, color);
		Primitives::bresenham(renderer, x2, y2, x4, y2, color);
    }
}

void Primitives::triangleFill(SDL_Renderer *renderer, Point2D p1, Point2D p2, Point2D p3, ColorRGBA color)
{
	triangleFill(renderer, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color);
}

void Primitives::triangle(SDL_Renderer *renderer, int x1, int y1, int x2 ,int y2, int x3, int y3, ColorRGBA color)
{
	Primitives::bresenham(renderer, x1, y1, x2, y2, color);
	Primitives::bresenham(renderer, x2, y2, x3, y3, color);
	Primitives::bresenham(renderer, x1, y1, x3, y3, color);
}

void Primitives::triangle(SDL_Renderer *renderer, Point2D p1, Point2D p2, Point2D p3, ColorRGBA color)
{
	triangle(renderer, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y,color);
}


/*---------------- CONVEX POLYGON--------------------------------*/

double Primitives::PolygonHelper::cross(const Point2D & O, const Point2D & A, const Point2D & B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

std::vector<Point2D> Primitives::PolygonHelper::convexHull(std::vector<Point2D> P)
{
	int n = P.size();
	int k = 0;
	std::vector<Point2D> H;
    H.reserve(2*n);

	std::sort(P.begin(), P.end(), [](Point2D p, Point2D q){return p<q;});

	//build upper hull
	for(int i=0; i<n; i++)
	{
		while(k>=2 && PolygonHelper::cross(H[k-2], H[k-1], P[i]) <=0)
			k--;

		H[k++] = P[i];
	}

	for(int i=n-2, t = k+1; i>=0; i--)	
	{
		while (k >= t && PolygonHelper::cross(H[k-2], H[k-1], P[i]) <= 0) 
			k--;

		H[k++] = P[i];
	}

	H.resize(k);
	return H;
}

void Primitives::polygonFill(SDL_Renderer *renderer, const std::vector<Point2D> & points, ColorRGBA color)
{
	std::vector<Point2D> convexPoints = PolygonHelper::convexHull(points);
	Primitives::bresenham(renderer, convexPoints[0], convexPoints[2], color);
	for(int i=0; i< convexPoints.size()-2; i++)
	{
		Primitives::triangleFill(renderer, convexPoints[0], convexPoints[i+1], convexPoints[i+2], color);
	}
}

void Primitives::polygon(SDL_Renderer *renderer, const std::vector<Point2D> & points, ColorRGBA color)
{
	std::vector<Point2D> convexPoints = PolygonHelper::convexHull(points);
	//Primitives::bresenham(renderer, convexPoints[0], convexPoints[2], color);
	for(int i=0; i< convexPoints.size(); i++)
	{
		Primitives::bresenham(renderer, convexPoints[i], convexPoints[i+1], color);
	}
	Primitives::bresenham(renderer, convexPoints[0], convexPoints[convexPoints.size()-1], color);
}