#include <Line.h>

Line::Line(int xstart, int ystart, int xend, int yend) : m_currentPoint(Point2D(xstart,ystart)),
														m_endPoint(Point2D(xend, yend))
{
	int dx = abs(xend - xstart);
	int dy = abs(yend - ystart);
	twodx = 2*dx;
	twody = 2*dy;
	twodydx = twody - twodx;
	slope_less_one = (dx>dy) ? true : false;
	xinc = (xend>xstart ? 1 : -1);
	yinc = (yend>ystart ? 1 : -1);	
	p = (slope_less_one) ? (twody-dx) : (twodx - dy);
}

Line::Line(const Point2D & start, const Point2D & end) : Line(start.x, start.y, end.x, end.y)
{
}

bool Line::nextPoint(void)
{
	if(m_currentPoint == m_endPoint)
			return false;

	if(slope_less_one)
	{
		m_currentPoint.x += xinc;

		if(p<0)
		{
			p += twody;	
		}

		else
		{	
			m_currentPoint.y += yinc;
			p += twodydx;
		}
		return true;
	}

	m_currentPoint.y += yinc;
	if(p <0)
		p += twodx;
	else
	{
		m_currentPoint.x += xinc;
		p -= twodydx;
	}
	return true;
}

void Line::draw(SDL_Renderer *renderer, ColorRGBA color)
{
	setPixel(renderer, m_currentPoint.x, m_currentPoint.y, color);
	while(nextPoint())
	{
		setPixel(renderer, m_currentPoint.x, m_currentPoint.y, color);
	}
}