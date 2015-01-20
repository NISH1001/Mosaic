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
	renderer.SetPixel(p.x, p.y, ColorRGBA(100,200,255,255));
}


void Render()
{
	Point2D p1(10,100);
	Point2D p2(200, 100);
	Point2D p3(15, 50);
	Vec3 v1(100,100,100);
	Vec3 v2(25,50,125);
	p1.attributes[0] = v1;
	p2.attributes[0] = v2;
	p3.attributes[0] = v1-v2; // (75, 50, -25)
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
