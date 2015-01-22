#include <Renderer.h>
#include <iostream>
#include <Polygon.h>

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

	/*
	if(!m_renderer)
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	if(!m_renderer)
	{
		
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}
	*/

	if(!m_screen)
		m_screen = SDL_GetWindowSurface(m_window);

	if(!m_screen)
	{
		std::cout << "cannot get window surface" << std::endl;
		return false;
	}

	m_depthBuffer = new float[m_width*m_height];

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


        std::string title = "FPS: " + std::to_string(m_timer.GetFPS());
        SDL_SetWindowTitle(m_window, title.c_str());

        SDL_LockSurface(m_screen);
        this->Clear();

        /*
		for(int i=0;i<100;i++)
        	SetPixel(i,i, ColorRGBA(255,0,0,0));
        */

        m_timer.Update(m_update);

        m_render();
        /*
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderClear(m_renderer);
		SDL_RenderPresent(m_renderer);
		*/

		SDL_UnlockSurface(m_screen);
		SDL_UpdateWindowSurface(m_window);
		//SDL_Delay(1);
	}
}

void Renderer::DrawModels(std::vector<Model>& models, Vertex3D(*vShader)(Vertex3D), void(*fShader)(Point2D&))
{
	std::vector<Vertex3D> tVertices; // to store vertices after transformation
	int numVertices;
	for(int i=0;i<models.size(); i++)
	{
		numVertices = models[i].m_vertices.size();
		tVertices.resize(numVertices);

		for(int j=0;j<numVertices;j++)
			tVertices[j] = vShader(models[i].m_vertices[j]);
		// backface culling and rendering triangles
		// checking in indexbuffer
		for(int j=0;j<models[i].m_indices.size();j+=3)
		{
			int a = models[i].m_indices[j],
				b = models[i].m_indices[j+1],
				c = models[i].m_indices[j+2];
			// calculate c for backface culling
			float C = tVertices[a].position.x * (tVertices[b].position.y - tVertices[c].position.y) +
					  tVertices[b].position.x * (tVertices[c].position.y - tVertices[a].position.y) +
					  tVertices[c].position.x * (tVertices[a].position.y - tVertices[b].position.y);
			// since the view vector is along z axis(0,0,1), we may just check 
			//  the sign of c because, the dot product result is c
			// NOW, if c is +ve, ignore the triangle and do not draw it
			// if c is -ve, draw the triangle
			if (C < 0)
			{
				// create point2D s and send to DrawTriangle
				Point2D p1(tVertices[a].position.x, tVertices[a].position.y),
					p2(tVertices[b].position.x, tVertices[b].position.y),
					p3(tVertices[c].position.x, tVertices[b].position.y);
				p1.depth = tVertices[a].position.z;
				p2.depth = tVertices[b].position.z;
				p3.depth = tVertices[c].position.z;
				p1.attributes[0] = tVertices[a].normal.ToVec3();
				p2.attributes[0] = tVertices[b].normal.ToVec3();
				p3.attributes[0] = tVertices[c].normal.ToVec3();
				// send to Rasterizer::drawtriangle the three normalized vertices
				Rasterizer::DrawTriangle(p1,p2,p3,fShader,m_depthBuffer);
			}
		}
	}

}

void Renderer::CleanUp(void)
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
