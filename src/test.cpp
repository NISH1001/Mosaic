#include <Rasterizer.h>

void fragShad(Point2D&p1)
{
	return;
}

int main()
{
	Point2D p1(5,15);
	Point2D p2(15, 10);
	Point2D p3(10, 4);
	Vec3 v1(100,100,100);
	Vec3 v2(25,50,125);
	p1.attributes[0] = v1;
	p2.attributes[0] = v2;
	p3.attributes[0] = v1-v2; // (75, 50, -25)
	Rasterizer rast;
	float *depth;
	int w = 100, h = 100;
	rast.DrawTriangle(p1,p3,p2,w,h,&fragShad, depth);
}
