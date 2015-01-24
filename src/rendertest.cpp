#include <iostream>
#include <Renderer.h>
#include <Matrix.h>
#include <Transform.h>
#include <Rasterizer.h>
#include <Model.h>

int WIDTH = 800;
int HEIGHT = 600;

std::string filename = "cube.obj";

float angle = 0.f;

// projection and view matrices
Mat4 PROJECTION, MODELVIEW;
// main renderer
Renderer renderer; 

/*make sure it is multiple of 3
	position,normal,color
*/
Vertex3D vertices3d[] = {
				{ Vec3(0,0,0), Vec3(0,0,0), Vec3(255,0,0)},
				{ Vec3(100,0,0), Vec3(0,0,0), Vec3(255,0,0)},
				{ Vec3(0,100,0), Vec3(0,0,0), Vec3(255,0,0)},
				{ Vec3(0,0,200), Vec3(0,0,0), Vec3(255,0,0)},
				{ Vec3(0,50,0), Vec3(0,0,0), Vec3(255,0,0)},
				{ Vec3(300,0,0), Vec3(0,0,0), Vec3(255,0,0)},
			};
unsigned numvertices3D = sizeof(vertices3d)/sizeof(Vertex3D);

// OUR LONG AWAITED CUBE
// vertices
Vec3 v1(50,0,50), vc1(255,0,0);
Vec3 v2(50,0,0), vc2(0,255,0);
Vec3 v3(0,0,0), vc3(0,0,255);
Vec3 v4(0,0,50), vc4(255,255,0);
Vec3 v5(50,50,50), vc5(0,255,255);
Vec3 v6(50,50,0), vc6(255,0,255);
Vec3 v7(0,50,0), vc7(0,120,55);
Vec3 v8(0,50,50), vc8(55,255,0);
// normals
Vec3 n1(0,1,0), n2(0,0,1), n3(1,0,0), n4(0,-1,0), n5(0,0,-1), n6(-1,0,0);

Vertex3D verticesCube[] ={
	{v1,n2,vc1},{v5,n2,vc5},{v4,n2,vc4},{v4,n2,vc4},{v5,n2,vc5},{v8,n2,vc8},
	{v1,n3,vc1},{v2,n3,vc2},{v5,n3,vc5},{v5,n3,vc5},{v2,n3,vc2},{v6,n3,vc6},
	{v2,n5,vc2},{v3,n5,vc3},{v6,n5,vc6},{v6,n5,vc6},{v3,n5,vc3},{v7,n5,vc7},
	{v3,n6,vc3},{v8,n6,vc8},{v7,n6,vc7},{v8,n6,vc8},{v3,n6,vc3},{v4,n6,vc4},
	{v8,n1,vc8},{v5,n1,vc5},{v7,n1,vc7},{v7,n1,vc7},{v5,n1,vc5},{v6,n1,vc6},
	{v4,n4,vc4},{v3,n4,vc3},{v1,n4,vc1},{v1,n4,vc1},{v3,n4,vc3},{v2,n4,vc2},
};

unsigned numCube = sizeof(verticesCube)/sizeof(Vertex3D);

// models
std::vector<Model> models;

void Update(double dt)
{
	//std::cout << dt << std::endl;
}

// Fragment shader, receives a point and renders it in framebuffer
void FragmentShader(Point2D& p)
{
	Vec3 att = p.attributes[0];
	renderer.SetPixel(p.x, p.y, ColorRGBA(att.x,att.y,att.z,255));
}

// vertex shader, receives a vertex and multiplies it with modelview and projection matrix
Mat4 SCALE = Transform::Scale(Vec3(50,50,50), Vec3(0,0,0));
Vertex3D VertexShader(Vertex3D vertex)
{
	Vec4 image = PROJECTION * MODELVIEW * Transform::RotateY(renderer.m_angle)*
					SCALE * vertex.position;
	//image.NormalizeByW();
	Vec4 normal = MODELVIEW * Vec4(vertex.normal, 0.f);
	return Vertex3D(image, normal.ToVec3(), vertex.color);
}


void Render()
{
	/*
	// for testing DrawTriangle()
	Point2D p1(100,100);
	Point2D p2(0,0);
	Point2D p3(200,0);
	Vec3 v(1,2,3);
	p1.attributes[0] = p2.attributes[0] = p3.attributes[0] = v;
	float * f;
	Rasterizer::DrawTriangle(p1,p2,p3,WIDTH, HEIGHT, &FragmentShader, f);
	*/
	renderer.DrawModels(models, &VertexShader, &FragmentShader);
}


int main()
{
	//PROJECTION = Transform::GetPerspective(90.f * 3.141592/180, float(WIDTH)/HEIGHT, 100.f, 800.f);
	PROJECTION = Transform::GetOrthographic(500,-500,500,-500,-500,500);
	MODELVIEW = Transform::LookAt(Vec3(0, 100, 100), Vec3(0,0,0));

	models.push_back(Model("cube.obj"));

	Vec4 v(0,100,50,1);
	//std::cout << MODELVIEW*v;
//	return 2;

	if(renderer.Initialize("rendertest", 50, 100, WIDTH, HEIGHT))
	{
		renderer.SetUpdateCallback(&Update);
		renderer.SetRenderCallback(&Render);
		renderer.MainLoop();
		renderer.CleanUp();
	}
}
