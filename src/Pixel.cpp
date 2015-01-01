#include "include/Pixel.h"

Pixel::Pixel(SDL_Renderer * renderer, ColorRGBA color)
{
	SDL_RenderDrawColor(renderer, color.R, color.G, color.B, color.A);
}




