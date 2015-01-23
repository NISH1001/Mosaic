#include <Renderer.h>
#include <helper.h>
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

        m_timer.Update(m_update);

        m_render();

	SDL_UnlockSurface(m_screen);
	SDL_UpdateWindowSurface(m_window);
	}
}

void Renderer::DrawModels(std::vector<Model>& models, Vertex3D(*vShader)(Vertex3D), void(*fShader)(Point2D&))
{
	std::vector<Vertex3D> tVertices; // to store vertices after transformation
	int numVertices;
	for(int i=0;i<models.size(); i++)
	{
		numVertices = models[i].m_vertexBuffer.size();

		for(int j=0;j<numVertices;j++)
			tVertices.push_back(vShader(models[i].m_vertexBuffer[j]));
		// backface culling and rendering triangles
		// checking in indexbuffer
		for(int j=0;j<models[i].m_indexBuffer.size();j+=3)
		{
			int a = models[i].m_indexBuffer[j],
				b = models[i].m_indexBuffer[j+1],
				c = models[i].m_indexBuffer[j+2];

			// calculate C for backface culling
			float C = Helper::GetC(tVertices[a].position, tVertices[b].position, tVertices[c].position);

			// since the view vector is along z axis(0,0,1), we may just check 
			//  the sign of c because, the dot product result is c
			// NOW, if c is +ve, ignore the triangle and do not draw it
			// if c is -ve, draw the triangle
			if (C < 0)
			{
				//first normalize
				tVertices[a].position.NormalizeByW();
				tVertices[b].position.NormalizeByW();
				tVertices[c].position.NormalizeByW();
				// create point2D s and send to DrawTriangle, here we convert to device coordinates so that in Rasteriser::
				//  DrawTriangle, we can do clippint with respect to device coordinates
				Point2D p1(ROUND(tVertices[a].position.x*m_width/2.f+m_width/2.f), ROUND(tVertices[a].position.y*(-m_height/2.f)+m_height/2.f)),
				p2(ROUND(tVertices[b].position.x*m_width/2.f+m_width/2.f), ROUND(tVertices[b].position.y*(-m_height/2.f)+m_height/2.f)),
				p3(ROUND(tVertices[c].position.x*m_width/2.f+m_width/2.f), ROUND(tVertices[c].position.y*(-m_height/2.f)+m_height/2.f));
				p1.depth = tVertices[a].position.z;
				p2.depth = tVertices[b].position.z;
				p3.depth = tVertices[c].position.z;
				p1.attributes[0] = tVertices[a].color;
				p2.attributes[0] = tVertices[b].color;
				p3.attributes[0] = tVertices[c].color;
				// send to Rasterizer::drawtriangle the three normalized vertices
				Rasterizer::DrawTriangle(p1,p2,p3,m_width, m_height,fShader,m_depthBuffer);
			}
			else 
				std::cout << "hidden\n ";
		}
	}

}

void Renderer::CleanUp(void)
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
