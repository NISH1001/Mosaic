#pragma once

#include <SDL2/SDL.h>
#include <functional>
#include <Timer.h>
#include <pixel.h>

class Renderer
{
	public:
		Renderer(void) : m_window(NULL), m_renderer(NULL), m_screen(NULL), m_depthBuffer(NULL), 
							m_timer(150) , m_frameBuffer(NULL), m_clearColor(255,255,255,255)
		{}

		~Renderer() {}
		bool Initialize(const char*title, int x, int y, int width, int height);
		void MainLoop();
		void CleanUp();
		
		// callbacks
		//void SetRenderCallback(std::function<void()> renderCallback) { m_render = renderCallback; }
		void SetUpdateCallback(std::function<void(double)> updateCallback) { m_update = updateCallback; }
		//void SetResizeCallback(std::function<void(int, int)> resizeCallback) { m_resize = resizeCallback; }

		void SetPixel(int x, int y, ColorRGBA color)
		{
			if (x >= 0 && m_width && y >= 0 && y < m_height)
            {
            	uint32_t* p = (Uint32*)m_screen->pixels;
            	p[y*m_width + x] = (0xFF << 24) | (color.R << 16) | (color.G << 8) | color.B;
           	}

		}

	private:
		void Clear(void)
		{
			for (int i = 0; i < m_width; ++i)
			{
				for(int j=0; j< m_height; ++j)
				{
					SetPixel(i, j, m_clearColor);
				}
			}
		}
		

	private:
		Timer m_timer;

		uint32_t* m_frameBuffer;
		int m_width, m_height;
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		SDL_Surface* m_screen;
		float* m_depthBuffer;
		ColorRGBA m_clearColor;

		
		std::function<void(double)> m_update;
		//std::function<void()> m_render;
		//std::function<void(int,int)> m_resize;
		
};
