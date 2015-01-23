#pragma once

#include <vector>
#include <Vector.h>
#include <Matrix.h>
#include <iostream>
#include <tuple>
#include <utility>
#include <fstream>
#include <sstream>

/*this is just a test class for loading obj
	shall be integrate to Model class
*/

struct Vec2
{
	float x, y;
};

class ObjLoader
{
public:
	ObjLoader(const std::string & filename)
	{
		std::ifstream obj(filename,std::ios::in);

		std::string line;
		std::cout <<"inside objloader" << std::endl;
		while(std::getline(obj, line))
		{
			
			std::istringstream linestream(line);
			std::cout << line << std::endl;

		}
	}
public:
	std::vector<Vec4> m_vertices;
	std::vector<Vec3> m_normals;
	std::vector<Vec2> m_texcorods;
};