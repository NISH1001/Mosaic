#include <Triangle.h>

Triangle::Triangle(SDL_Renderer* renderer, Point2D p1, Point2D p2, Point2D p3, ColorRGBA color) : m_color(color), m_p1(p1), m_p2(p2), m_p3(p3)
{
	m_renderer = renderer;
}

Triangle::~Triangle()
{
}

void Triangle::Draw()
{
	Line(m_renderer, m_p1, m_p2, m_color).Draw();
	Line(m_renderer, m_p2, m_p3, m_color).Draw();
	Line(m_renderer, m_p3, m_p1, m_color).Draw();
}

void Triangle::SortY()
{
	if (m_p1.y > m_p2.y) 
	{
		std::swap(m_p1.x, m_p2.x);
		std::swap(m_p1.y, m_p2.y);
	}
	if (m_p2.y > m_p3.y) 
	{
		std::swap(m_p2.x, m_p3.x);
		std::swap(m_p2.y, m_p3.y);
	} ///largest yvalue coord is at 3
	if (m_p1.y > m_p2.y) 
	{
		std::swap(m_p1.x, m_p2.x);
		std::swap(m_p1.y, m_p2.y);
	}
}

void Triangle::FlatFill(int xt, int yt, int xb1, int xb2, int yb)
{
	if(yt == yb) return;
	
	Line line1(m_renderer, xt, yt, xb1, yb, m_color);
	line1.NextPoint();
	Line line2(m_renderer, xt, yt, xb2, yb, m_color);
	line2.NextPoint();
	
	while(1)
	{
		if((line1.m_currentPoint.x == xb1) &&  (line2.m_currentPoint.x==xb2))
			break;

		while(line1.m_currentPoint.y != line2.m_currentPoint.y)
		{
			if(!line1.NextPoint())
				break;
		}
		Line scanline(m_renderer, line1.m_currentPoint.x, line1.m_currentPoint.y, line2.m_currentPoint.x, line2.m_currentPoint.y, m_color);
		scanline.Draw();

		if(!line2.NextPoint()) break;
	}
}


void Triangle::DrawFilled()
{
<<<<<<< HEAD
}
=======
	SortY();
	
	int x1=m_p1.x, x2=m_p2.x, x3=m_p3.x;
	int y1=m_p1.y, y2=m_p2.y, y3=m_p3.y;

    if(y2 == y3)
    {
    	FlatFill(x1, y1, x2, x3, y2); // draw from bottom (x1,y1) to top horizontal vertices
    }

    else if(y1 == y2)
    {
    	FlatFill(x3, y3, x1, x2, y1); // draw from top (x3, y3) to bottom horizontal vertices
    }

    else
    {
		// finding the horizontal point to (x2, y2)
    	int x4 = x1 == x3 ? x1 : (x1 + (int)((y2 - y1) * 1.0 * (x3 - x1) / (y3 - y1)));

    	FlatFill(x1, y1, x2, x4, y2);
		FlatFill(x3, y3, x2, x4, y2);
		Line(m_renderer, x2, y2, x4, y2, m_color).Draw();
    }
}

>>>>>>> f6c4b6b69f29cd4ac041a448610966326e1ba33a
