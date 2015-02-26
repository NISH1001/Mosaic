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
	Model(Vertex3D *vertices, unsigned numvertices, Vertex3D(*vertShader)(const Vertex3D &), Vec3(*colShader)(Vertex3D, Vec3)=NULL);
    Model()
    {
        this->m_modelMatrix = Mat4(1.0f);
    }

	Model(const std::string & filename, Vertex3D(*vertShader)( const Vertex3D &), Vec3(*colShader)(Vertex3D, Vec3)=NULL)
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

    Model  operator = (const Model & other)
    {
        Model m;
        m.m_vertexBuffer = other.m_vertexBuffer;
        m.m_indexBuffer = other.m_indexBuffer;
        m.m_material = other.m_material;
        m.m_isFlat = other.m_isFlat;
        m.m_hasTexture = other.m_hasTexture;
        return m;
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

    void AddTransformation(const Mat4 & mat)
    {
        this->m_modelMatrix = mat * this->m_modelMatrix;
    }

    void ApplyTransformation(void)
    {
        unsigned vbsize = m_vertexBuffer.size();
        for(unsigned i=0; i<vbsize; ++i)
        {
            Vec4 pos = m_vertexBuffer[i].position;
            pos =  this->m_modelMatrix * pos;
            pos.NormalizeByW();
            m_vertexBuffer[i].position = pos;
            Vec4 norm = Vec4(m_vertexBuffer[i].normal, 0.f);
            norm = this->m_modelMatrix * norm;
            norm.NormalizeToUnit();
            m_vertexBuffer[i].normal = Vec3(norm.x, norm.y, norm.z);
        }
    }

public:
	Vertex3D(*vertexShader)( const Vertex3D&);
	Vec3(*colorShader)(Vertex3D, Vec3);

	std::vector<unsigned> m_indexBuffer;
	std::vector<Vertex3D> m_vertexBuffer;
	Material m_material;
	bool m_hasTexture;
	bool m_isFlat;

    Mat4 m_modelMatrix;
private:
	ObjLoader obj;	
};
