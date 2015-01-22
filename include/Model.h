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
	Vec3 pos; // the x,y,z coordinates
	Vec3 normal; // for normal
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

inline std::ostream& operator << (std::ostream &os, const Surface & s)
{
	os <<"(" << s.vertex[0].pos.x << "," << s.vertex[0].pos.y << "," << s.vertex[0].pos.z << ")";
	os << ", ";
	os <<"(" << s.vertex[1].pos.x << "," << s.vertex[1].pos.y << "," << s.vertex[1].pos.z << ")";
	os << ", ";
	os <<"(" << s.vertex[2].pos.x << "," << s.vertex[2].pos.y << "," << s.vertex[2].pos.z << ")";
	return os;
}


class Model
{
public:
	Model(Vertex3D *vertices, unsigned numvertices);
	std::vector<Surface>::iterator GetSurfaceIterator(void)
	{
		std::vector<Surface>::iterator iter;
		iter = m_surfaces.begin();
		return iter;
	}
public:
	std::vector<Surface> m_surfaces;
	std::vector<int> m_indicesSurface;
	std::vector<Vertex3D> m_vertices;
};