#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#define pi 3.1415926536

float rad(float dec)
{
    return pi*dec/180.f;
}

class Vec3
{
public:
    struct { float x, y, z;};

    Vec3(float xx, float yy, float zz=0) : x(xx),y(yy), z(zz) {}
    Vec3() { z = 0;}

    Vec3 operator+(const Vec3& v) const
    {
        return Vec3(x+v.x, y+v.y, z+v.z);
    }  
    
    Vec3 operator-(const Vec3& v) const
    {
        return Vec3(x-v.x, y-v.y, z-v.z);
    }   

    bool operator==(const Vec3& v) const
    {
        return (x==v.x and y==v.y and z==v.z);
    }
};

// prototype for indexOf() function
int indexOf(Vec3 v, std::vector<Vec3> & vertices);

class Mat2
{
public:
    float m[2][2];
    Mat2(float m11, float m12, float m21, float m22)
    {
        m[0][0] = m11;  m[0][1] = m12;  m[1][0] = m21;  m[1][1] = m22;
    }

    Vec3 operator*(const Vec3& v) const
    {
        return Vec3(m[0][0]*v.x+m[0][1]*v.y, m[1][0]*v.x+m[1][1]*v.y);
    }
};


class Cube
{
public:
    float length;
    Vec3 points[8];
    unsigned int indxVert[8];

    Cube(Vec3 baseLeft, Vec3 baseRight, Vec3 topRight, Vec3 topLeft, float len)
    {
        points[0] = baseLeft;
        points[1] = baseRight;
        points[2] = topRight;
        points[3] = topLeft;
        points[4] = points[5] = points[6] = points[7] = Vec3(0,0,0);
        length = len;
    }

    void Store3DPoints()
    {
        Vec3 temp(0,0,length);
        points[4] = points[0] + temp;
        points[5] = points[1] + temp;
        points[6] = points[2] + temp;
        points[7] = points[3] + temp;
    }
    
    void getIndices(std::vector<Vec3> & vertices)
    {
        for(int i=0;i<8;i++)
        {
            int ind = indexOf(points[i], vertices);
            if(ind < 0) // means no vertex in vertex buffer, append the vertex to the vertex buffer
            {
                vertices.push_back(points[i]);
                indxVert[i] = vertices.size();
            }
            else // means the vertex is in the vertex buffer, ind is the index of vertex in buffer, +1 already done
            {
                indxVert[i] = ind;
            }
        }
    }

};

int indexOf(Vec3 v, std::vector<Vec3> & vertices)
{
    for(int i=0;i<vertices.size();i++)
    {
        if(vertices[i]==v)
            return i+1;
    }
    return -1;
}



std::vector<Cube> cubes; // where we store the cubes
std::vector<Vec3> vertBuff; // the vertex buffer where all the vertices are placed
float thetaChild = pi/4.0f;
float childLenFactor = cos(thetaChild);


void generate(Vec3 baseleft, Vec3 baseright, float thetacube, float length, float iter, std::string text)
{
    if (iter<0) return;

    Mat2 rot(cos(thetacube), -sin(thetacube), sin(thetacube), cos(thetacube)); // rotating the points

    Vec3 topleft = baseleft + Vec3(0, length);
    // first translate the baseleft to origin and then only rotate
    topleft = topleft - baseleft;
    topleft = rot * topleft;
    topleft = topleft+baseleft; 

    Vec3 topright = baseright + Vec3(0, length);
    // same here, first translate the origin;
    topright = topright - baseright;
    topright = rot * topright;
    topright = topright + baseright;

    //std::cout << text<< "  "<<iter<< std::endl;
    //std::cout << "baseleft:("<<baseleft.x<<","<<baseleft.y<<")"<< " baseright:("<<baseright.x<<","<<baseright.y<<")"<< " topleft:("<<topleft.x<<","<<topleft.y<<")"<< " topright:("<<topright.x<<","<<topright.y<<")"<< std::endl<<std::endl;

    // add to the cubes
    Cube c(baseleft, baseright, topright, topleft, length);
    c.Store3DPoints();
    cubes.push_back(c); 
    
    // process further to children 

    float base = childLenFactor * length* cos(thetaChild); // length at top from left side whoser upper point will have right base for child1
    float height = childLenFactor * length* sin(thetaChild); // height at top from base of top side
    
    Vec3 temp;
    temp = topleft + Vec3(base, height);

    temp = temp - topleft;
    // rotation matrix to find the point above the upper face of the square/cube
    rot = Mat2(cos(thetacube), -sin(thetacube), sin(thetacube), cos(thetacube));
    temp = rot * temp;
    temp = temp + topleft;

    // now we have upper point for the child

    // generate from the first child(left one)
    generate(topleft, temp, thetacube+thetaChild, length*childLenFactor, iter-1, std::string("leftchild"));
    // generate from the second child
    generate(temp, topright, thetacube+thetaChild-pi/2.f, length*sqrt(1-pow(childLenFactor,2)), iter-1, std::string("rightchild"));
}

int main()
{
    std::ofstream outfile("objects/tree.obj");

    float length = 5.f;
    Vec3 baseleft(0,0), baseright(length, 0);
    generate(baseleft, baseright, 0, length, 7, std::string("base"));
    // by this point, we have all the cubes with 8 vertices in cubes vector

    // so at first get the indices of cube vertices in the vertex buffer 
    for(int i=0;i<cubes.size();i++)
        cubes[i].getIndices(vertBuff);
    // respective vertices are stored in cubes' index array by now

/*    for(int i=0;i<vertBuff.size();i++)
        std::cout <<i+1 << " "<<vertBuff[i].x << " "<<vertBuff[i].y<<" "<<vertBuff[i].z<<std::endl;
    std::cout << vertBuff.size();
    */


    // write the vertices to the file
    for(int i=0;i<vertBuff.size();i++)
       outfile << "v " <<vertBuff[i].x << " "<<vertBuff[i].y<<" "<<vertBuff[i].z<<"\n";

    // write an arbitrary normal to file (since, flatshading, we dont need its exact value, just for parsing)
    outfile << "\nvn 0.0 1.0 0.0\n\n";

    // the turn of faces now
    for(int i=0;i<cubes.size();i++)
    {
        outfile << "f "<<cubes[i].indxVert[0]<<"//1 "
                       <<cubes[i].indxVert[1]<<"//1 "
                       <<cubes[i].indxVert[2]<<"//1\n";

        outfile << "f "<<cubes[i].indxVert[0]<<"//1 "
                       <<cubes[i].indxVert[2]<<"//1 "
                       <<cubes[i].indxVert[3]<<"//1\n";

        outfile << "f "<<cubes[i].indxVert[1]<<"//1 "
                    <<cubes[i].indxVert[5]<<"//1 "
                    <<cubes[i].indxVert[6]<<"//1\n";

        outfile << "f "<<cubes[i].indxVert[1]<<"//1 "
                      <<cubes[i].indxVert[6]<<"//1 "
                      <<cubes[i].indxVert[2]<<"//1\n";

        outfile << "f "<<cubes[i].indxVert[5]<<"//1 "
                        <<cubes[i].indxVert[4]<<"//1 "
                        <<cubes[i].indxVert[7]<<"//1\n";

        outfile << "f "<<cubes[i].indxVert[5]<<"//1 "
                    <<cubes[i].indxVert[7]<<"//1 "
                    <<cubes[i].indxVert[6]<<"//1\n";

        outfile << "f "<<cubes[i].indxVert[4]<<"//1 "
                         <<cubes[i].indxVert[0]<<"//1 "
                         <<cubes[i].indxVert[3]<<"//1\n";

        outfile << "f "<<cubes[i].indxVert[4]<<"//1 "
                        <<cubes[i].indxVert[3]<<"//1 "
                        <<cubes[i].indxVert[7]<<"//1\n";

        outfile << "f "<<cubes[i].indxVert[3]<<"//1 "
                        <<cubes[i].indxVert[2]<<"//1 "
                        <<cubes[i].indxVert[6]<<"//1\n";

        outfile << "f "<<cubes[i].indxVert[3]<<"//1 "
                         <<cubes[i].indxVert[6]<<"//1 "
                         <<cubes[i].indxVert[7]<<"//1\n";

        outfile << "f "<<cubes[i].indxVert[0]<<"//1 "
                        <<cubes[i].indxVert[4]<<"//1 "
                        <<cubes[i].indxVert[5]<<"//1\n";
                        
        outfile << "f "<<cubes[i].indxVert[0]<<"//1 "
                        <<cubes[i].indxVert[5]<<"//1 "
                        <<cubes[i].indxVert[1]<<"//1\n";
    }
    outfile.close();
    return 0;
}
