#ifndef PIXEL_H
#define PIXEL_H

#include <SDL2/SDL.h>

struct ColorRGBA
{
        ColorRGBA(int r, int g, int b, int a) : R(r), G(g), B(b), A(a) {}
        int R, G, B, A;
};

inline void setPixel(SDL_Renderer *renderer, int x, int y, ColorRGBA color)
{
        SDL_Rect pixel = {x, y, 1, 1};
        SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
        SDL_RenderFillRect(renderer, &pixel);
}

#endif //PIXEL_H
