#pragma once

#include <SDL2/SDL.h>
#include <Point2D.h>

// class for color
struct ColorRGBA
{
		ColorRGBA()
		{
			R=255;G=255;B=255;A=255;
		}
        ColorRGBA(int r, int g, int b, int a) : R(r), G(g), B(b), A(a) {}
        int R, G, B, A;
};

// plotting pixel
inline void setPixel(SDL_Renderer *renderer, int x, int y, ColorRGBA color)
{
        SDL_Rect pixel = {x, y, 1, 1};
        SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
        SDL_RenderFillRect(renderer, &pixel);
}

inline void setPixel(SDL_Renderer * renderer, Point2D p, ColorRGBA color)
{
	SDL_Rect pixel = {p.x, p.y, 1,1};
    SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
    SDL_RenderFillRect(renderer, &pixel);
}

