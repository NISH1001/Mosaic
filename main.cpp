#include <algorithm>
#include <assert.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <pixel.h>
#include <Primitives.h>
#include <Point2D.h>
#include <Line.h>

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
	
	//Primitives::triangle(renderer, Point2D(10,550), Point2D(10,400), Point2D(50, 450), ColorRGBA(255,0,0,0));
	//Primitives::triangleFill(renderer, 50, 400, 200, 100, 100,500, ColorRGBA(255,0,0,0));
	//Primitives::triangleFill(renderer, 600, 20, 400, 200, 200,50, ColorRGBA(255,0,0,0));
	//Primitives::triangleFill(renderer, Point2D(400,300), Point2D(800,0), Point2D(800,100), ColorRGBA(255,0,0,0));
	

	//std::vector<Point2D> points = {	Point2D(200,50), Point2D(400,400), Point2D(100,300)	};
	std::vector<Point2D> points = {	Point2D(400,0), Point2D(200,100), Point2D(700,150), Point2D(700,200), Point2D(200,200), Point2D(400,50),
									Point2D(400,400)};
	Primitives::polygonFill(renderer, points, ColorRGBA(255,0,0,0));
	
	SDL_RenderPresent(renderer);
	
	SDL_Delay(1000 * 3);

	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;	

}
