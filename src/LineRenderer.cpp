#include "include/LineRenderer.h"

LineRenderer::LineRenderer(SDL_Renderer * renderer, ColorRgba color) : 
	m_pixel(renderer, color)
{
}

LineRenderer::~LineRenderer()
{
}


