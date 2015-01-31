#include <Ellipse.h>

Ellipse::~Ellipse()
{}

Ellipse::Ellipse(SDL_Renderer *renderer, int cx, int cy, int rx, int ry, ColorRGBA color) : m_cx(cx),m_cy(cy),m_rx(rx),m_ry(ry),m_color(color)
{
	m_renderer = renderer;
}

Ellipse::Ellipse(SDL_Renderer *renderer, Point2D center, int rx, int ry, ColorRGBA color) : Ellipse(renderer, center.x, center.y, rx, ry, color)
{
}


void Ellipse::PlotSymmetry(int x, int y)
{
	setPixel(m_renderer, m_cx+x, m_cy+y, m_color);
	setPixel(m_renderer, m_cx-x, m_cy+y, m_color);
	setPixel(m_renderer, m_cx+x, m_cy-y, m_color);
	setPixel(m_renderer, m_cx-x, m_cy-y, m_color);
}


void Ellipse::Draw()
{
	int rx2 = m_rx * m_rx;
	int ry2 = m_ry * m_ry;
	int tworx2 = 2 * rx2;
	int twory2 = 2 * ry2;
	
	int x = 0;
	int y = m_ry;

	int p = ry2 - rx2*m_ry + rx2/4.f + 0.5f;
	
	PlotSymmetry(x, y);
	
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
		
		PlotSymmetry(x, y);
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
		
		PlotSymmetry(x, y);
	}
}

void Ellipse::DrawFilled()
{
	int rx2 = m_rx * m_rx;
	int ry2 = m_ry * m_ry;
	int tworx2 = 2 * rx2;
	int twory2 = 2 * ry2;
	
	int x = 0;
	int y = m_ry;

	int p = ry2 - rx2*m_ry + rx2/4.f + 0.5f;
	
	Line(m_renderer, m_cx+x, m_cx+y, m_cx-x, m_cy+y, m_color).Draw();
	
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
		
		Line(m_renderer, m_cx+x, m_cx+y, m_cx-x, m_cy+y, m_color).Draw();
		Line(m_renderer, m_cx+x, m_cx-y, m_cx-x, m_cy-y, m_color).Draw();
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
		
		Line(m_renderer, m_cx+x, m_cx+y, m_cx-x, m_cy+y, m_color).Draw();
		Line(m_renderer, m_cx-x, m_cx+y, m_cx-x, m_cy-y, m_color).Draw();
	}
}
