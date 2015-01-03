#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <pixel.h>
#include <Primitives.h>
#include <Point2D.h>
#include <Line.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void triangle(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int x3, int y3, ColorRGBA color)
{
    Primitives::bresenham(renderer, x1, y1, x2, y2 , color);
    Primitives::bresenham(renderer, x2, y2, x3, y3, color);
    Primitives::bresenham(renderer, x3, y3, x1, y1, color);
}

int main()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout<<"cannot initialize"<<std::endl;
		return -1;
	}

	SDL_Window *window =SDL_CreateWindow("circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	
	if(!window)
		return -1;

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer)
			{
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

    Primitives::triangleFlatFill(renderer, 400, 50, 100, 700, 200, ColorRGBA(255,0,0,0));
    Primitives::triangleFlatFill(renderer, 400, 400, 100, 700, 200, ColorRGBA(255,0,0,0));
	
	SDL_RenderPresent(renderer);
	
	SDL_Delay(3000);

	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;	

}
