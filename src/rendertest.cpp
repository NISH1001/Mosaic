#include <iostream>
#include <Renderer.h>
#include <Rasterizer.h>

Renderer renderer; 

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
	Point2D p2(0, 200);
	Point2D p3(50, 20);
	Vec3 v1(255,0,0);
	Vec3 v2(111,255,0);
	Vec3 v3(0,200,255);
	p1.attributes[0] = v1;
	p2.attributes[0] = v2;
	p3.attributes[0] = v3;
	Rasterizer rast;
	float *t;
	int a =  500;
	rast.DrawTriangle(p1,p2,p3,a,a, &FragmentShader, t);// test only
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
