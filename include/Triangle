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
		//These are helper functions
		
		/* the FlatFill function takes a vertex, not horizontal to any
		  other and other two vertices which are horizontal
		  (xb1,yb) and (xb2, yb) 
		 */
		void FlatFill(int xt, int yt, int xb1, int xb2, int yb);

		void SortY();

	private:
		SDL_Renderer * m_renderer;
		ColorRGBA m_color;
};
