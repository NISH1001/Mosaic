#include <Line.h>

Line::Line(SDL_Renderer* renderer, int xstart, int ystart, int xend, int yend, ColorRGBA color) : m_currentPoint(Point2D(xstart,ystart)),
	m_endPoint(Point2D(xend, yend)), m_color(color)
{
	m_renderer = renderer;

	dx = abs(xend - xstart);
	dy = abs(yend - ystart);
	twodx = 2*dx;
	twody = 2*dy;
	twodydx = twody - twodx;
	slope_less_one = (dx>dy) ? true : false;
	xinc = (xend>xstart ? 1 : -1);
	yinc = (yend>ystart ? 1 : -1);	
	p = (slope_less_one) ? (twody-dx) : (twodx - dy);
}

Line::Line(SDL_Renderer*renderer, const Point2D & start, const Point2D & end, ColorRGBA color) : Line(renderer, start.x, start.y, end.x, end.y, color)
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


void Line::Draw()
{
	int x = m_currentPoint.x;
	int y = m_currentPoint.y;
	setPixel(m_renderer, x, y, m_color);
	if (dx > dy)
	{
		// p is already calculated
		for(int i=0;i<dx;i++)
		{
			if (p < 0)
				p+= twody;
			else
			{
				y+=yinc;
				p+=(twodydx);// twodydx = twody-twodx
			}
			x+=xinc;
			setPixel(m_renderer, x, y, m_color);
		}
	} 
	else
	{
		// p is already calculated
		for(int i=0;i<dy;i++)
		{
			if (p < 0)
				p+= twodx;
			else
			{
				x+=xinc;
				p-=twodydx; // twodydx = twody-twodx, we need twodx-twody so
			}
			y+= yinc;
			setPixel(m_renderer, x, y, m_color);
		}
	}
}

void Line::DrawFilled()
{
	Draw();
}
