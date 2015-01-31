#pragma once
#include <Primitive.h>
#include <Triangle.h>

class Polygon : public Primitive // only convex polygon
{
	public:
		Polygon();
		Polygon(SDL_Renderer*, Point2D, Point2D, Point2D, Point2D, ColorRGBA);
		~Polygon();

		virtual void Draw();
		virtual void DrawFilled();

		// attributes
		Point2D m_p1, m_p2, m_p3, m_p4;

	private:
		SDL_Renderer * m_renderer;
		ColorRGBA m_color;
};

