#pragma once
#include <Primitive.h>
#include <Line.h>
#include <Point2D.h>

class Triangle : public Primitive
{
	public:
		Triangle(SDL_Renderer* renderer, Point2D p1, Point2D p2, Point2D p3, ColorRGBA color);
		~Triangle();

		virtual void Draw();
		virtual void DrawFilled();

		// attributes
		Point2D m_p1, m_p2, m_p3;

	private:
		SDL_Renderer * m_renderer;
		ColorRGBA m_color;
};
