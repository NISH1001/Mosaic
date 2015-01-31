#include <Polygon.h>

Polygon::Polygon(SDL_Renderer*renderer, Point2D p1, Point2D p2, Point2D p3, Point2D p4, ColorRGBA color) :
	m_p1(p1), m_p2(p2), m_p3(p3), m_p4(p4), m_color(color)
{
	m_renderer = renderer;
}

Polygon::~Polygon()
{
}

void Polygon::Draw()
{
	Line(m_renderer, m_p1, m_p2, m_color).Draw();
	Line(m_renderer, m_p2, m_p3, m_color).Draw();
	Line(m_renderer, m_p3, m_p4, m_color).Draw();
	Line(m_renderer, m_p4, m_p1, m_color).Draw();
}

void Polygon::DrawFilled()
{
	Triangle(m_renderer, m_p1, m_p2, m_p3, m_color).DrawFilled();
	Triangle(m_renderer, m_p3, m_p4, m_p1, m_color).DrawFilled();
}
