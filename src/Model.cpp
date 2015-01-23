#include <Model.h>

//accepts vertices array
Model::Model(Vertex3D *vertices, unsigned numvertices) 
{
	// if ... return immediately
	if(numvertices%3 != 0 || numvertices==0)
	{
		std::cout << "invalid no. of vertices" << std::endl;
		return;
	}

	//we dont need this variable now
//	unsigned numsurfaces = numvertices/3;

	//this too
//	m_surfaces.resize(numsurfaces);

	//first create the VB and IB
	for(unsigned i=0; i<numvertices; ++i)
	{
		Vertex3D currentpoint = vertices[i];
		size_t vsize = m_vertexBuffer.size();
		std::pair<bool, unsigned> status = Lookup(currentpoint);

		//if current point is already in VB only store the index in IB
		if(status.first == true)
		{
			m_indexBuffer.push_back(status.second);
		}

		//if nwew point then store both vertex and index
		else
		{
			m_vertexBuffer.push_back(currentpoint);
			m_indexBuffer.push_back(status.second);
		}
		

		//Vertex3D v = m_vertexBuffer[m_indexBuffer.back()];
		//std::cout << v << std::endl;
	}

	//std::cout << m_indexBuffer.size() << std::endl;
	//std::cout << m_vertexBuffer.size() << std::endl;
	size_t ibsize = m_indexBuffer.size();

	// now order the indices
//	for(unsigned i=0; i<ibsize; i+=3)
	{
//		Order(m_indexBuffer[i], m_indexBuffer[i+1], m_indexBuffer[i+2]); commented because this wont let backface culling as all are arranged clockwise
	}

	//for test
	for(unsigned i=0; i<ibsize; i+=3)
	{
		Vertex3D v1 = m_vertexBuffer[m_indexBuffer[i]];
		Vertex3D v2 = m_vertexBuffer[m_indexBuffer[i+1]];
		Vertex3D v3 = m_vertexBuffer[m_indexBuffer[i+2]];
		//std::cout << v1 << std::endl;
		//std::cout << v2 << std::endl;
		//std::cout << v3 << std::endl;
	}

	//we dont need this now
/*	for(int i=0; i<numsurfaces; i+=3)
	{
		Vertex3D v1 = vertices[i];
		Vertex3D v2 = vertices[i+1];
		Vertex3D v3 = vertices[i+2];
		m_surfaces.push_back(Surface(v1,v2,v3));
	}
	*/
}

/*
//not needed now
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
// not needed now
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

*/
