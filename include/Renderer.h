#pragma once

#include <SDL2/SDL.h>


class Renderer
{
	public:
		Renderer(const char*title, int x, int y, int width, int height);
		~Renderer();
		void MainLoop();
		void CleanUp();
		// callbacks
		void SetRenderCallback(std::function<void()> renderCallback) { m_render = renderCallback; }
		void SetUpdateCallback(std::function<void(double)> updateCallback) { m_update = updateCallback; }
		void SetResizeCallback(std::function<void(int, int)> resizeCallback) { m_resize = resizeCallback; }

	private:
		uint32_t* m_frameBuffer;
		int m_width, m_height;

		SDL_Window* m_window;
		SDL_Surface* m_screen;
		float* m_depthBuffer;
};
