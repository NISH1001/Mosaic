#include <iostream>
#include <SDL2/SDL.h>
#include "paradoxlib/pixel.h"
#include "paradoxlib/bresenham.h"
#include "paradoxlib/circle.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

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

	circleFill(renderer, 400, 300, 100, ColorRGBA(255,0,0,0));
	
	SDL_RenderPresent(renderer);
	
	SDL_Delay(2000);

	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;	

}
