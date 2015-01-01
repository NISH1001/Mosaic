#pragma once

class LineRenderer
{
	public:
		LineRenderer(SDL_Renderer *renderer, ColorRGBA color);
		~LineRenderer();

		// set the render color to the specified color
		void setRenderColor(ColorRGBA color);
		// draw line, input two endpoints
		draw(int x1, int y1, int x2, int y2);
};

