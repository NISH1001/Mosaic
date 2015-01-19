#include <Rasterizer.h>

void fragShad(Point2D&p1)
{
	int a;
	return;
}

int main()
{
	Point2D p1(5,5);
	Point2D p2(10, 10);
	Point2D p3(15, 8);
	Vec3 v1(100,100,100);
	Vec3 v2(25,50,125);
	Vec3 v3(200,-200,200);
	p1.attributes[0] = v1;
	p2.attributes[0] = v2;
	p3.attributes[0] = v1-v2;
	Rasterizer rast;
	float *depth;
	int w = 100, h = 100;
	rast.DrawTriangle(p1,p2,p3,w,h,&fragShad, depth);
}
