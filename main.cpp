#include <iostream>
#include <SDL2/SDL.h>
#include "src/primitives.cpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
//using namespace Primitives;

int main()
{
	int r, rx, ry, xc, yc;
	std::cout << "Enter the radius of circle:";
	std::cin >> r;
	fflush(stdin);
	std::cout << "Enter the x-radius of ellipse:";
	std::cin >> rx; 
	fflush(stdin);
	std::cout << "Enter y-radius of ellipse:";
	std::cin >> ry;
	fflush(stdin);
	std::cout << "Enter the Xcenter:";
	std::cin >> xc;
	fflush(stdin);
	std::cout << "Enter the Ycenter:";
	std::cin >> yc;

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

	Primitives::circle(renderer, xc, yc, r, ColorRGBA(255,0,0,0));
	Primitives::ellipse(renderer, xc, yc, rx, ry, ColorRGBA(255,0,0,0));
	
	SDL_RenderPresent(renderer);
	
	SDL_Delay(3000);

	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;	

}
