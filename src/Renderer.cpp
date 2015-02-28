#include <Renderer.h>
#include <helper.h>
#include <iostream>
#include <Matrix.h>

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

	m_depthBuffer = new float[(m_width+1)*(m_height+1)];

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
			m_keyboard(&event);
			
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
		// clear depth buffer
		//ClearDepthBuffer();
	}
}

void Renderer::ClearDepthBuffer()
{
	for(unsigned i=0;i<m_width*m_height;i++)
		m_depthBuffer[i] = -1;
}

void Renderer::DrawModels(std::vector<Model> models, Vertex3D(*vShader)(const Vertex3D&), void(*fShader)(Point2D&))
{
	std::vector<Vertex3D> tVertices; // to store vertices after transformation
	int numVertices;

	for(int i=0;i<models.size(); i++)
	{
		numVertices = models[i].m_vertexBuffer.size();

		m_currentMaterial = &(models[i].m_material);
        m_currentModelMatrix = &(models[i].m_modelMatrix);

		//just resize -> push_back will be slow as it has to resize after every element added
		tVertices.resize(numVertices);
		for(int j=0;j<numVertices;j++)
        {
            tVertices[j] = vShader(models[i].m_vertexBuffer[j]);
            //avoid divide by zero case
            if(tVertices[j].position.w ==0.0f)
                tVertices[j].position.w = 0.000001f;
            else if(tVertices[j].position.w < 0)
                tVertices[j].position.w *= -1;
        }

		// backface culling and rendering triangles
		// checking in indexbuffer
		unsigned ibsize = models[i].m_indexBuffer.size();
		for(int j=0;j<ibsize;j+=3)
		{
			int a = models[i].m_indexBuffer[j],
			    b = models[i].m_indexBuffer[j+1],
			    c = models[i].m_indexBuffer[j+2];
				
			Vec4 &v1 = tVertices[a].position;
			Vec4 &v2 = tVertices[b].position;
			Vec4 &v3 = tVertices[c].position;
            

			//do the clipping if object is behind the camera
            if( ( v1.x < -v1.w && v2.x < -v2.w && v3.x < -v3.w  )  ||        
                ( v1.y < -v1.w && v2.y < -v2.w && v3.y < -v3.w  )  || 
                ( v1.z < -v1.w && v2.z < -v2.w && v3.z < -v3.w  )  || 

                ( v1.x > v1.w && v2.x > v2.w && v3.x > v3.w  )  ||                 
                ( v1.y > v1.w && v2.y > v2.w && v3.y > v3.w  )  ||                
                ( v1.z > v1.w && v2.z > v2.w && v3.z > v3.w  ) 
              )
                continue;

			//first normalize
				v1.NormalizeByW();
				v2.NormalizeByW();
				v3.NormalizeByW();


			// calculate C for backface culling
			float C = Helper::GetC(v1, v2, v3);

            // temporary -> just for correcting the culling for flatshading
            if(models[i].m_isFlat)
                C = -C;


			// since the view vector is along z axis(0,0,1), we may just check 
			//  the sign of c because, the dot product result is c
			// NOW, if c is -ve, ignore the triangle and do not draw it
			// if c is +ve, draw the triangle
			if ( C < 0)
			{	
				
				// create point2D s and send to DrawTriangle, here we convert to device coordinates so that in Rasteriser::
				//  DrawTriangle, we can do clipping with respect to device coordinates
				Point2D p1(static_cast<int>(v1.x*m_width/2.f+m_width/2.f), static_cast<int>(v1.y*(-m_height/2.f)+m_height/2.f)),
						p2(static_cast<int>(v2.x*m_width/2.f+m_width/2.f), static_cast<int>(v2.y*(-m_height/2.f)+m_height/2.f)),
						p3(static_cast<int>(v3.x*m_width/2.f+m_width/2.f), static_cast<int>(v3.y*(-m_height/2.f)+m_height/2.f));
				
				if(models[i].m_isFlat)
				{
					Vec3 color, normal;
					Vec4 va,vb,vc;
					va=models[i].m_vertexBuffer[a].position;
					vc=models[i].m_vertexBuffer[c].position;
					vb=models[i].m_vertexBuffer[b].position;
					normal = GetNormal(va, vb, vc);
					normal.NormalizeToUnit();
					color = models[i].colorShader(models[i].m_vertexBuffer[j],normal);
					tVertices[a].color = tVertices[b].color = tVertices[c].color = color;
				}

				p1.depth = v1.z;
				p2.depth = v2.z;
				p3.depth = v3.z;

				p1.attributes[0] = tVertices[a].color;
				p1.attributes[1] = tVertices[a].normal;

				p2.attributes[0] = tVertices[b].color;
				p1.attributes[1] = tVertices[b].normal;

				p3.attributes[0] = tVertices[c].color;
				p3.attributes[1] = tVertices[c].normal;
				// send to Rasterizer::drawtriangle the three normalized vertices
				Rasterizer::DrawTriangle(p1,p2,p3,m_width, m_height,fShader,m_depthBuffer);
			}
			//else 
				//std::cout << "hidden\n ";
		}
	}

}

void Renderer::CleanUp(void)
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
