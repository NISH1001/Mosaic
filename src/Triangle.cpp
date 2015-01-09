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

void Triangle::DrawFilled()
{
	
