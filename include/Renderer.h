#pragma once

#include <SDL2/SDL.h>
#include <functional>
#include <Timer.h>

class Renderer
{
	public:
		Renderer(void) : m_window(NULL), m_renderer(NULL), m_screen(NULL), m_depthBuffer(NULL), m_timer(150) {}
		~Renderer() {}
		bool Initialize(const char*title, int x, int y, int width, int height);
		void MainLoop();
		void CleanUp();
		
		// callbacks
		//void SetRenderCallback(std::function<void()> renderCallback) { m_render = renderCallback; }
		void SetUpdateCallback(std::function<void(double)> updateCallback) { m_update = updateCallback; }
		//void SetResizeCallback(std::function<void(int, int)> resizeCallback) { m_resize = resizeCallback; }
		

	private:
		Timer m_timer;
		//uint32_t* m_frameBuffer;
		int m_width, m_height;

		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		SDL_Surface* m_screen;
		float* m_depthBuffer;

		
		std::function<void(double)> m_update;
		//std::function<void()> m_render;
		//std::function<void(int,int)> m_resize;
		
};
