#include <Circle.h>

Circle::~Circle()
{}

Circle::Circle(SDL_Renderer *renderer, int cx, int cy, int r, ColorRGBA color) : m_color(color), m_cx(cx),m_cy(cy),m_r(r)
{
	m_renderer = renderer;
}

Circle::Circle(SDL_Renderer *renderer, Point2D center, int r, ColorRGBA color)
{
	Circle::Circle(renderer, center.x, center.y, r, color);
}

void Circle::PlotSymmetry(int x, int y)
{
	setPixel(m_renderer, m_cx+x, m_cy+y, m_color);
	setPixel(m_renderer, m_cx+x, m_cy-y, m_color);
	setPixel(m_renderer, m_cx-x, m_cy+y, m_color);
	setPixel(m_renderer, m_cx-x, m_cy-y, m_color);
	setPixel(m_renderer, m_cx+y, m_cy+x, m_color);
	setPixel(m_renderer, m_cx+y, m_cy-x, m_color);
	setPixel(m_renderer, m_cx-y, m_cy+x, m_color);
	setPixel(m_renderer, m_cx-y, m_cy-x, m_color);
}

void Circle::Draw()
{
	int x = 0;
    int y = m_r;
    int p = 1-m_r;
    
    PlotSymmetry(x, y);
    
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
        
        PlotSymmetry(x, y);
    } 
}

void Circle::DrawFilled()
{
	int x = 0;
    int y = m_r;
    int p = 1-m_r;
    
	Line(m_renderer, m_cx+x, m_cy+y, m_cx-x,m_cy+y, m_color).Draw();
    
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
        
		Line(m_renderer, m_cx+x, m_cy+y, m_cx-x,m_cy+y, m_color).Draw();
		Line(m_renderer, m_cx+x, m_cy-y, m_cx-x,m_cy-y, m_color).Draw();
		Line(m_renderer, m_cx+y, m_cy+x, m_cx-y,m_cy+x, m_color).Draw();
		Line(m_renderer, m_cx+y, m_cy-x, m_cx-y,m_cy-x, m_color).Draw();
    } 
}

