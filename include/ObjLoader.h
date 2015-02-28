#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


#include <Vector.h>
#include <Matrix.h>
#include <Point2D.h>
#include <helper.h>

/*this is just a test class for loading obj
	shall be integrate to Model class
*/

class ObjLoader
{
public:
	ObjLoader() {}

	ObjLoader(const std::string & filename){ Load(filename); }

	bool Load(const std::string & filename)
	{
		//create an input file stream to read
		std::ifstream obj(filename,std::ios::in);

		//if cant open return
		if(!obj.is_open())
		{
			std::cout << "cannot open" << std::endl;
			return false;
		}

  		//our temporary vectors for storing
  		std::vector<Vec4> vertices;
  		std::vector<Vec3> normals;
  		std::vector<Vec2> texcoords;
  		std::vector<Vec3> faceindices; //vec3 cuz -> vertexindex, texcoordindex, normalindex

  		bool m_hasTexture = false;

  		//get each line read into this variable
		std::string line;
		while(std::getline(obj, line))
		{
			//if any leading whitespaces remove them
			Helper::LeftTrim(line);

			//if any trailing whitespaces remove them
			Helper::RightTrim(line);

			//now get our linestream using istringstream
			std::istringstream linestream(line);
			

			std::string key;
			linestream >> key;

			//check if vertex
			if(key == "v")
			{
				Vec4 v;
				linestream >> v.x;
				linestream >> v.y;
				linestream >> v.z;
				if(!(linestream >> v.w))
				{
					v.w = 1.0f;
				}

				v.NormalizeByW();
				//std::cout << v << std::endl;
				vertices.push_back(v);
			}

			//check if vertex normal
			else if(key == "vn")
			{
				Vec3 v;
				linestream >> v.x;
				linestream >> v.y;
				linestream >> v.z;
				//std::cout << v << std::endl;
				normals.push_back(v);
			}

			//check if texture coordinate
			else if(key == "vt")
			{
				m_hasTexture = true;
				Vec2 v;
				linestream >> v.x;
				linestream >> v.y;
				//std::cout << v << std::endl;
				texcoords.push_back(v);
			}

			else if(key == "f")
			{
				//remove 'f' character from the line
				line = line.substr(1, line.length()-1);

				//remove leading whitespaces
				Helper::LeftTrim(line);

				//if no UV(texcoords) -> // change to default /0/
				line = Helper::ReplaceAll(line, "//", "/0/");
				//now replace all '/' character to white spaces
				line = Helper::ReplaceAll(line, "/", " ");

				//now create our stream for line
				std::istringstream lstream(line);

				/*store the v/vt,vn indices into faceindices
					every 3 indices make up a triangular surface
					x = vertex index
					y = texcoord index
					z = normal index
				*/
				Vec3 v[3];
				lstream >> v[0].x;
				lstream >> v[0].y;
				lstream >> v[0].z;
				lstream >> v[1].x;
				lstream >> v[1].y;
				lstream >> v[1].z;
				lstream >> v[2].x;
				lstream >> v[2].y;
				lstream >> v[2].z;
				//std::cout << v[0] << ", " << v[1] << ", "<< v[2] << std::endl;
				faceindices.push_back(v[0]);
				faceindices.push_back(v[1]);
				faceindices.push_back(v[2]);
			}

		}
		obj.close();

		unsigned numvertices = vertices.size();
		unsigned numfaces = faceindices.size();

		m_vertexBuffer.resize(numvertices);

		for(unsigned i=0; i<numfaces; i+=3)
		{
			//std::cout << vertices[i] << std::endl;
			Vec3 v[3];
			Vertex3D v3d[3];
			v[0] = faceindices[i];
			v[1] = faceindices[i+1];
			v[2] = faceindices[i+2];
			//std::cout << v[0] << ", " << v[1] << ", "<< v[2] << std::endl;
			v3d[0].position = vertices[v[0].x-1];
			v3d[0].normal = normals[v[0].z-1];
			v3d[0].color = Vec3(255,0,0);
			v3d[1].position = vertices[v[1].x-1];
			v3d[1].normal = normals[v[1].z-1];
			v3d[1].color = Vec3(0,255,0);
			v3d[2].position = vertices[v[2].x-1];
			v3d[2].normal = normals[v[2].z-1];
			v3d[2].color = Vec3(0,0,255);

			v3d[0].normal = (v3d[0].normal + m_vertexBuffer[v[0].x-1].normal);
			v3d[0].normal.NormalizeToUnit();
			v3d[1].normal = (v3d[1].normal + m_vertexBuffer[v[1].x-1].normal);
			v3d[1].normal.NormalizeToUnit();
			v3d[2].normal = (v3d[2].normal + m_vertexBuffer[v[2].x-1].normal);
			v3d[2].normal.NormalizeToUnit();

			m_vertexBuffer[v[0].x-1] = v3d[0];
			m_vertexBuffer[v[1].x-1] = v3d[1];
			m_vertexBuffer[v[2].x-1] = v3d[2];

			m_indexBuffer.push_back(faceindices[i].x-1);
			m_indexBuffer.push_back(faceindices[i+1].x-1);
			m_indexBuffer.push_back(faceindices[i+2].x-1);
		}

		size_t ibsize = m_indexBuffer.size();
		size_t vbsize = m_vertexBuffer.size();

        std::cout << std::endl << filename << std::endl;
		std::cout << "IndexBuffer size : " << ibsize << std::endl;
		std::cout << "VertexBuffer size : " << vbsize << std::endl;
        
		return true;
	}

private:

public:
	std::vector<unsigned> m_indexBuffer;
	std::vector<Vertex3D> m_vertexBuffer;
	bool m_hasTexture;
};
