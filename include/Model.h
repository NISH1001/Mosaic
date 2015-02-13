#pragma once
#include <vector>
#include <Vector.h>
#include <Matrix.h>
#include <Transform.h>
#include <iostream>
#include <tuple>
#include <utility>
#include <ObjLoader.h>
#include <Point2D.h>
#include <Material.h>


/*a triangular surface struct
	vertices in counter-cockwise
	v[0] = rightmost vertex
	v[2] = leftmost point in the order
	normal is the surface normal
*/

/*
	A general Model Class
	consists of Surfaces
	Accepts an array of 3d vertices that has triangles in continuous way
	or Accepts an array of surfaces
*/
class Model
{
public:
	Model(Vertex3D *vertices, unsigned numvertices, Vertex3D(*vertShader)(Vertex3D&), Vec3(*colShader)(Vertex3D, Vec3)=NULL);

	Model(const std::string & filename, Vertex3D(*vertShader)(Vertex3D&), Vec3(*colShader)(Vertex3D, Vec3)=NULL)
	{
		if(obj.Load(filename))
		{
			m_indexBuffer = obj.m_indexBuffer;
			m_vertexBuffer = obj.m_vertexBuffer;
			m_hasTexture = obj.m_hasTexture;
		}
		vertexShader = vertShader;
		colorShader = colShader;
		if(colorShader==NULL)
			m_isFlat=false;
		else
			m_isFlat=true;
		
	}

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

    void Translate(float tx, float ty, float tz);
    void Translate(const Vec3& t)
    {
        Translate(t.x, t.y, t.z);
    }

    void RotateX(float angle);
    void RotateY(float angle);
    void RotateZ(float angle);
    void Rotate(float angle, const Vec3& vec, const Vec3& point);

    void Scale(float sx, float sy, float xz);
    void Scale(const Vec3& sc, const Vec3& vec);
    void Scale(const Vec3 & sc)
    {
        Scale(sc.x, sc.y, sc.z);
    }

public:
	Vertex3D(*vertexShader)(Vertex3D&);
	Vec3(*colorShader)(Vertex3D, Vec3);

	std::vector<unsigned> m_indexBuffer;
	std::vector<Vertex3D> m_vertexBuffer;
	Material m_material;
	bool m_hasTexture;
	bool m_isFlat;
private:
	ObjLoader obj;	
};
