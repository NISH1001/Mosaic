#include <Model.h>

Model::Model(Vertex3D *vertices, unsigned numvertices) 
{
	if(numvertices%3 != 0)
	{
		std::cout << "numvertices is not multiple of 3" << std::endl;
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