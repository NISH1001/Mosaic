#pragma once

#include <vector>
#include <iostream>
#include <locale>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

#include <Vector.h>
#include <Matrix.h>
#include <Point2D.h>


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

		/* //test
		std::ofstream myfile;
  		myfile.open ("test.txt");
  		myfile << "Writing this to a file.\n";
  		myfile.close();
  		*/

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
			LeftTrim(line);

			//if any trailing whitespaces remove them
			RightTrim(line);

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
				LeftTrim(line);

				//if no UV(texcoords) -> // change to default /0/
				line = ReplaceAll(line, "//", "/0/");
				//now replace all '/' character to white spaces
				line = ReplaceAll(line, "/", " ");

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

			m_vertexBuffer[faceindices[i].x-1] = v3d[0];
			m_vertexBuffer[faceindices[i+1].x-1] = v3d[1];
			m_vertexBuffer[faceindices[i+2].x-1] = v3d[2];

			m_indexBuffer.push_back(faceindices[i].x-1);
			m_indexBuffer.push_back(faceindices[i+1].x-1);
			m_indexBuffer.push_back(faceindices[i+2].x-1);
		}
		size_t ibsize = m_indexBuffer.size();
		size_t vbsize = m_vertexBuffer.size();
		std::cout << "IndexBuffer size : " << ibsize << std::endl;
		std::cout << "VertexBuffer size : " << vbsize << std::endl;
		/*
		for(unsigned i=0; i<ibsize; i+=3)
		{
			Vertex3D v1 = m_vertexBuffer[m_indexBuffer[i]];
			Vertex3D v2 = m_vertexBuffer[m_indexBuffer[i+1]];
			Vertex3D v3 = m_vertexBuffer[m_indexBuffer[i+2]];
			std::cout << v1 << std::endl;
			std::cout << v2 << std::endl;
			std::cout << v3 << std::endl;
		}
		*/

		return true;
	}

private:
	//remove trailing  whitespaces
	std::string &RightTrim(std::string & str)
	{
		 str.erase(find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
		 return str;
	}

	//remove lieading whitespaces
	std::string &LeftTrim(std::string &str) 
	{
		 str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return str;
	}

	std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) 
	{
    	size_t start_pos = 0;
    	while((start_pos = str.find(from, start_pos)) != std::string::npos) 
    	{
        	str.replace(start_pos, from.length(), to);
        	start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    	}
    	return str;
	}

public:
	std::vector<unsigned> m_indexBuffer;
	std::vector<Vertex3D> m_vertexBuffer;
	bool m_hasTexture;
};