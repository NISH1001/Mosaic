#include <iostream>
#include <Renderer.h>
#include <Rasterizer.h>
#include <Model.h>

Renderer renderer; 
int w = 800;
int h = 600;

/*make sure it is multiple of 3
	pos,normal,color
*/
Vertex3D vertices3d[] = {
				{ Vec3(0,0,0), Vec3(0,0,0), Vec3(255,0,0)},
				{ Vec3(100,0,0), Vec3(0,0,0), Vec3(255,0,0)},
				{ Vec3(0,100,0), Vec3(0,0,0), Vec3(255,0,0)},
				{ Vec3(200,0,200), Vec3(0,0,0), Vec3(255,0,0)},
				{ Vec3(0,50,0), Vec3(0,0,0), Vec3(255,0,0)},
				{ Vec3(300,0,0), Vec3(0,0,0), Vec3(255,0,0)},
			};
unsigned numvertices3D = sizeof(vertices3d)/sizeof(Vertex3D);

Model triangles(vertices3d, numvertices3D);

void Update(double dt)
{
	//std::cout << dt << std::endl;
}

void FragmentShader(Point2D& p)
{
	Vec3 att = p.attributes[0];
	renderer.SetPixel(p.x, p.y, ColorRGBA(att[0],att[1],att[2],0));
}

Point2D vertices [6] = { Point2D(100,200),
						Point2D(0,200),
						Point2D(50,20),
						Point2D(400,0),
						Point2D(600,100),
						Point2D(200,200),
					};
int numvertices = sizeof(vertices)/sizeof(Point2D);

int indices[] = {
				0,1,2,
				3,4,5,
				0,1,3
			};
int numindices = sizeof(indices)/sizeof(int);

void Render()
{
	std::vector<Surface>::iterator iter = triangles.GetSurfaceIterator();
	for(;iter != triangles.m_surfaces.end(); ++iter)
	{
		std::cout << (*iter) << std::endl;
	}
	
	Vec3 v1(255,0,0);
	Vec3 v2(0,255,0);
	Vec3 v3(0,0,255);
	
	Rasterizer rast;
	float *t;
	for(int i=0; i<numindices; i+=3)
	{
		Point2D p1 = vertices[indices[i]];
		Point2D p2 = vertices[indices[i+1]];
		Point2D p3 = vertices[indices[i+2]];
		p1.attributes[0] = v1;
		p2.attributes[0] = v2;
		p3.attributes[0] = v3;
		rast.DrawTriangle(p1, p2, p3,
						w, h , &FragmentShader, t);
	}

}

int main()
{
	if(renderer.Initialize("rendertest", 50, 100, w, h))
	{
		renderer.SetUpdateCallback(&Update);
		renderer.SetRenderCallback(&Render);
		renderer.MainLoop();
		renderer.CleanUp();
	}
}
