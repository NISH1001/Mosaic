#ifndef PIXEL
#define PIXEL

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
//colors
extern ColorRGBA RED;
extern ColorRGBA GREEN;
extern ColorRGBA BLUE;
extern ColorRGBA WHITE;
extern ColorRGBA BLACK;
/*
ColorRGBA LIGHT_RED(250, 160, 122, 255);
ColorRGBA CRIMSON(220, 20, 60, 255);
ColorRGBA DARK_RED(139, 0, 0, 255);
ColorRGBA ORANGE(255, 69, 0, 255);
ColorRGBA YELLOW(255, 255, 0, 255);
ColorRGBA GOLD(255, 215, 0, 255);
ColorRGBA MAROON(128, 0, 0, 255);
ColorRGBA SKY_BLUE(135, 206,235, 255);
*/

#endif
