#pragma once

#include <Point2D.h>
#include <pixel.h>
#include <Line.h>

class Circle : public Primitive
{
	public:
		Circle(SDL_Renderer *renderer, int cx, int cy, int r, ColorRGBA color);
		Circle(SDL_Renderer *renderer, Point2D center, int r, ColorRGBA color);
		~Circle();

		virtual void Draw();
		virtual void DrawFilled();

		//attributes
		int m_cx, m_cy; // center
		int m_r;
	private:
		SDL_Renderer *m_renderer;
		ColorRGBA m_color;
		void PlotSymmetry(int x, int y);
};
