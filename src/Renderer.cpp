#include <Renderer.h>
#include <iostream>

bool Renderer::Initialize(const char* title, int x, int y, int width, int height)
{
	m_width = width;
	m_height = height;
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Cannot initialize sdl" << std::endl;
		return false;
	}

	if(!m_window)
		m_window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );

	if(!m_window)
	{
		std::cout << "cannot create window" << std::endl;
		return false;
	}

	if(!m_renderer)
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	if(!m_renderer)
	{
		
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	return true;

}

void Renderer::MainLoop(void)
{
	bool quit = false;
	SDL_Event event;

	while(!quit)
	{
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
        	{
        		case SDL_QUIT:
            		quit = true;
            		break;

        		case SDL_KEYDOWN:
        			switch (event.key.keysym.sym)
        			{
        				case SDLK_ESCAPE:
        					quit = true;
        					break;
        			}
        			break;
        		}
		}

		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderClear(m_renderer);
		SDL_RenderPresent(m_renderer);
		//std::cout << "MainLoop" << std::endl;
	}
}

void Renderer::CleanUp(void)
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
