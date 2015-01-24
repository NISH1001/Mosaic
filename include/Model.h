#pragma once
#include <vector>
#include <Vector.h>
#include <Matrix.h>
#include <iostream>
#include <tuple>
#include <utility>
#include <ObjLoader.h>
#include <Point2D.h>



/*a triangular surface struct
	vertices in counter-cockwise
	v[0] = rightmost vertex
	v[2] = leftmost point in the order
	normal is the surface normal
*/

//not needed now
class Surface
{
public:
	Vertex3D vertex[3];
	Surface() {} 
	Surface(Vertex3D v1, Vertex3D v2, Vertex3D v3)
	{
		Store(v1,v2,v3);
	}
private:
	void Store(Vertex3D  v1, Vertex3D  v2, Vertex3D  v3)
	{
		if(v1.position.x < v2.position.x)
		{
			std::swap(v1,v2);
		}

		if(v2.position.x < v3.position.x)
		{
			std::swap(v2,v3);
		}
		{
			std::swap(v1,v2);
		}

		if(v2.position.y > v3.position.y)
		{
			std::swap(v2,v3);
		}

		vertex[0] = v1;
		vertex[1] = v2;
		vertex[2] = v3;

	}
};

inline std::ostream& operator << (std::ostream &os, const Surface & s)
{
	os <<"(" << s.vertex[0].position.x << "," << s.vertex[0].position.y << "," << s.vertex[0].position.z << ")";
	os << ", ";
	os <<"(" << s.vertex[1].position.x << "," << s.vertex[1].position.y << "," << s.vertex[1].position.z << ")";
	os << ", ";
	os <<"(" << s.vertex[2].position.x << "," << s.vertex[2].position.y << "," << s.vertex[2].position.z << ")";
	return os;
}

/*
	A general Model Class
	consists of Surfaces
	Accepts an array of 3d vertices that has triangles in continuous way
	or Accepts an array of surfaces
*/
class Model
{
public:
	Model(Vertex3D *vertices, unsigned numvertices);

	Model(const std::string & filename)
	{
		if(obj.Load(filename))
		{
			m_indexBuffer = obj.m_indexBuffer;
			m_vertexBuffer = obj.m_vertexBuffer;
			m_hasTexture = obj.m_hasTexture;
		}
		
	}

	//we dont need this now
	Model(Surface *surfaces, unsigned numsurfaces);

	//we dont need this now
	/*std::vector<Surface>::iterator GetSurfaceIterator(void)
	{
		std::vector<Surface>::iterator iter;
		iter = m_surfaces.begin();
		return iter;
	}
	// a surface or surfaces
	//not needed void AddSurface(const Surface & surface) { m_surfaces.push_back(surface); }
	//not needed void AddSurfaces(Surface *surfaces, unsigned numsurfaces);

	 */
	//check if the point v is in VB
	std::pair<bool,unsigned> Lookup(const Vertex3D & v)
	{
		size_t vbsize = m_vertexBuffer.size();

		for(unsigned i=0; i<vbsize; ++i)
		{
			if(m_vertexBuffer[i] == v)
			{
				//std::cout << v.position.x << ", " << v.position.y << " " <<i << std::endl;
				return std::make_pair(true, i);
			}
		}
		return std::make_pair(false, vbsize);
	}

	//for ordering of indices of triangle
	// no need to swap vertices
	void Order(unsigned &i1, unsigned & i2, unsigned & i3)
	{
		if(m_vertexBuffer[i1].position.x < m_vertexBuffer[i2].position.x)
		{
			std::swap(i1,i2);
		}

		if(m_vertexBuffer[i2].position.x < m_vertexBuffer[i3].position.x)
		{
			std::swap(i2,i3);
		}

		if(m_vertexBuffer[i1].position.x < m_vertexBuffer[i2].position.x)
		{
			std::swap(i1,i2);
		}

		if(m_vertexBuffer[i2].position.y > m_vertexBuffer[i3].position.y)
		{
			std::swap(i2,i3);
		}
	}


public:
	//we dont need this now
	/*
	std::vector<Vertex3D> m_vertices;
	std::vector<unsigned> m_indices;
	std::vector<Surface> m_surfaces;
	*/

	//we only need this
	std::vector<unsigned> m_indexBuffer;
	std::vector<Vertex3D> m_vertexBuffer;
	bool m_hasTexture;
private:
	ObjLoader obj;	
};
