#pragma once

#include <Point2D.h>
#include <pixel.h>
#include <Line.h>

class Ellipse : public Primitive
{
	public:
		Ellipse(SDL_Renderer * renderer, int cx, int cy, int rx, int ry, ColorRGBA color);
		Ellipse(SDL_Renderer * renderer, Point2D center, int rx, int ry, ColorRGBA color);
		~Ellipse();

		virtual void Draw();
		virtual void DrawFilled();

		//attributes
		int m_cx, m_cy; // center
		int m_rx;
		int m_ry;
	private:
		SDL_Renderer* m_renderer;
		ColorRGBA m_color;
		void PlotSymmetry(int x, int y);
};


