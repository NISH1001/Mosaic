#include <Model.h>

//accepts vertices array
Model::Model(Vertex3D *vertices, unsigned numvertices) 
{
	if(numvertices%3 != 0 || numvertices==0)
	{
		std::cout << "invalid no. of vertices" << std::endl;
		return;
	}

	unsigned numsurfaces = numvertices/3;
	m_surfaces.resize(numsurfaces);

	for(int i=0; i<numsurfaces; ++i)
	{
		Vertex3D v1 = vertices[i];
		Vertex3D v2 = vertices[i+1];
		Vertex3D v3 = vertices[i+2];
		m_surfaces.push_back(Surface(v1,v2,v3));
	}
}

//accepts surfaces array
Model::Model(Surface* surfaces, unsigned numsurfaces)
{
	if(numsurfaces == 0)
	{
		std::cout << "null surfaces..." << std::endl;
		return ;
	}

	for(int i=0; i<numsurfaces; i++)
	{
		m_surfaces.push_back(surfaces[i]);
	}
}

//add surfaces 
inline void Model::AddSurfaces(Surface *surfaces, unsigned numsurfaces)
{
	if(numsurfaces == 0)
	{
		std::cout << "null surfaces..." << std::endl;
		return ;
	}

	for(int i=0; i<numsurfaces; i++)
	{
		m_surfaces.push_back(surfaces[i]);
	}	
}