#include <iostream>
#include <Renderer.h>
#include <Rasterizer.h>

Renderer renderer; 

struct Vertex 
{
	Vec3 v; // the x,y,z coordinates
	Vec3 color; // for the color
	Vec3 normal; // for normal
//	Vec2 texture; // for texture coordinate
}

void Update(double dt)
{
	//std::cout << dt << std::endl;
}

void FragmentShader(Point2D& p)
{
	Vec3 att = p.attributes[0];
	renderer.SetPixel(p.x, p.y, ColorRGBA(att[0],att[1],att[2],0));
}


void Render()
{
	Point2D p1(100,200);
	Point2D p2(0, 300);
	Point2D p3(50, 20);
	Vec3 v1(255,0,255);
	Vec3 v2(111,255,149);
	Vec3 v3(120,200,255);
	p1.attributes[0] = v1;
	p2.attributes[0] = v2;
	p3.attributes[0] = v3;
	Rasterizer rast;
	float *t;
	int w = 800;
	int h = 600;
	rast.DrawTriangle(p1,p2,p3,w,h, &FragmentShader, t);// test only

}

int main()
{
	if(renderer.Initialize("rendertest", 50, 100, 800, 600))
	{
		renderer.SetUpdateCallback(&Update);
		renderer.SetRenderCallback(&Render);
		renderer.MainLoop();
	}

	renderer.CleanUp();
}
