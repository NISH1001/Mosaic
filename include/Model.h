#pragma once
#include <vector>
#include <Vector.h>
#include <Matrix.h>
#include <iostream>
#include <tuple>
#include <utility>

/*a 3D vertex struct
	a vertex has its position
	a color attribute
	a normal attribute
*/

struct Vertex3D
{
	Vec4 pos; // the x,y,z coordinates
	Vec3 normal; // for normal
	Vec3 color; // for the color

	bool operator == (const Vertex3D & v)
	{
		return (pos.x==v.pos.x && pos.y==v.pos.y && pos.z==v.pos.z);
	}
};


/*a triangular surface struct
	vertices in counter-cockwise
	v[0] = rightmost vertex
	v[2] = leftmost point in the order
	normal is the surface normal
*/
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
		if(v1.pos.x < v2.pos.x)
		{
			std::swap(v1,v2);
		}

		if(v2.pos.x < v3.pos.x)
		{
			std::swap(v2,v3);
		}

		if(v1.pos.x < v2.pos.x)
		{
			std::swap(v1,v2);
		}

		if(v2.pos.y > v3.pos.y)
		{
			std::swap(v2,v3);
		}

		vertex[0] = v1;
		vertex[1] = v2;
		vertex[2] = v3;

	}
};

inline std::ostream& operator << (std::ostream & os, const Vertex3D & v)
{
	os<< v.pos.x << " " << v.pos.y << " " << v.pos.z;
	return os;
}

inline std::ostream& operator << (std::ostream &os, const Surface & s)
{
	os <<"(" << s.vertex[0].pos.x << "," << s.vertex[0].pos.y << "," << s.vertex[0].pos.z << ")";
	os << ", ";
	os <<"(" << s.vertex[1].pos.x << "," << s.vertex[1].pos.y << "," << s.vertex[1].pos.z << ")";
	os << ", ";
	os <<"(" << s.vertex[2].pos.x << "," << s.vertex[2].pos.y << "," << s.vertex[2].pos.z << ")";
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
	Model(Surface *surfaces, unsigned numsurfaces);
	std::vector<Surface>::iterator GetSurfaceIterator(void)
	{
		std::vector<Surface>::iterator iter;
		iter = m_surfaces.begin();
		return iter;
	}
	// a surface or surfaces
	void AddSurface(const Surface & surface) { m_surfaces.push_back(surface); }
	void AddSurfaces(Surface *surfaces, unsigned numsurfaces);

	std::pair<bool,unsigned> Lookup(const Vertex3D & v)
	{
		size_t vbsize = m_vertexBuffer.size();

		for(unsigned i=0; i<vbsize; ++i)
		{
			if(m_vertexBuffer[i] == v)
			{
				//std::cout << v.pos.x << ", " << v.pos.y << " " <<i << std::endl;
				return std::make_pair(true, i);
			}
		}
		return std::make_pair(false, vbsize);
	}

	void Order(unsigned &i1, unsigned & i2, unsigned & i3)
	{
		if(m_vertexBuffer[i1].pos.x < m_vertexBuffer[i2].pos.x)
		{
			std::swap(i1,i2);
		}

		if(m_vertexBuffer[i2].pos.x < m_vertexBuffer[i3].pos.x)
		{
			std::swap(i2,i3);
		}

		if(m_vertexBuffer[i1].pos.x < m_vertexBuffer[i2].pos.x)
		{
			std::swap(i1,i2);
		}

		if(m_vertexBuffer[i2].pos.y > m_vertexBuffer[32].pos.y)
		{
			std::swap(i2,i3);
		}
	}


public:
	std::vector<Surface> m_surfaces;
	std::vector<unsigned> m_indexBuffer;
	std::vector<Vertex3D> m_vertexBuffer;
};