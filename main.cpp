#include <algorithm>
#include <assert.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <pixel.h>
#include <Primitives.h>
#include <Point2D.h>
#include <Line.h>
#include <Transform.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


int main()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout<<"cannot initialize"<<std::endl;
		return -1;
	}

	SDL_Window *window =SDL_CreateWindow("transform", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	
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

	std::vector<Point2D> points = {Point2D(400,0), Point2D(200,100), Point2D(600, 100)};
	Primitives::polygonFill(renderer, points, ColorRGBA(255,0,0,0));

	//std::vector<Point2D> scaled = Transform::scale(points, 400, 400, 0.5, 0.5);
	std::vector<Point2D> rotated = Transform::rotate(points, 400,100,180);
	std::vector<Point2D> translated = Transform::translate(rotated, 0,50);
	std::vector<Point2D> scaled = Transform::scale(translated, 400,100, 2*0.5, 0.5);
	Primitives::polygonFill(renderer, scaled, ColorRGBA(255,0,0,0));	
	
	SDL_RenderPresent(renderer);
	
	SDL_Delay(1000 * 3);

	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;	

}
