#pragma once
#include <vector>
#include <Vector.h>
#include <Matrix.h>
#include <iostream>

/*a 3D vertex struct
	a vertex has its position
	a color attribute
	a normal attribute
*/

struct Vertex3D
{
	Vertex3D(){}
	~Vertex3D(){}
	Vertex3D(Vec4 pos, Vec4 norm, Vec3 col):position(pos), normal(norm), color(col){}
	Vec4 position; // the x,y,z,w coordinates
	Vec4 normal; // for normal
	Vec3 color; // for the color
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
		if(v1.position.x < v2.position.x)
		{
			std::swap(v1,v2);
		}

		if(v2.position.x < v3.position.x)
		{
			std::swap(v2,v3);
		}

		if(v1.position.x < v2.position.x)
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
public:
	std::vector<Surface> m_surfaces;
	std::vector<int> m_indices;
	std::vector<Vertex3D> m_vertices;
};
