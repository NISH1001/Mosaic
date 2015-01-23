#include <iostream>
#include <Renderer.h>
#include <Matrix.h>
#include <Transform.h>
#include <Rasterizer.h>
#include <Model.h>

int WIDTH = 640;
int HEIGHT = 480;

// projection and view matrices
Mat4 PROJECTION, MODELVIEW;
// main renderer
Renderer renderer; 

/*make sure it is multiple of 3
	position,normal,color
*/
Vertex3D vertices3d[] = {
				{ Vec3(-4000,0,0), Vec3(0,0,0), Vec3(255,0,0)},
				{ Vec3(100,0,0), Vec3(0,0,0), Vec3(255,0,0)},
				{ Vec3(0,100,0), Vec3(0,0,0), Vec3(255,0,0)},/*
				{ Vec3(200,0,200), Vec3(0,0,0), Vec3(255,0,0)},
				{ Vec3(0,50,0), Vec3(0,0,0), Vec3(255,0,0)},
				{ Vec3(300,0,0), Vec3(0,0,0), Vec3(255,0,0)},*/
			};
unsigned numvertices3D = sizeof(vertices3d)/sizeof(Vertex3D);
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
	renderer.SetPixel(p.x, p.y, ColorRGBA(123,234,45,255));
}

// vertex shader, receives a vertex and multiplies it with modelview and projection matrix
Vertex3D VertexShader(Vertex3D vertex)
{
	Vec4 image = PROJECTION * MODELVIEW * vertex.position;
	image.NormalizeByW();
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
	PROJECTION = Transform::GetPerspective(120.f * 3.141592/180, float(WIDTH)/HEIGHT, 100.f, 800.f);
	MODELVIEW  = Transform::LookAt(Vec3(0, 0, 100), Vec3(0,0,0));

	models.push_back(Model(vertices3d, numvertices3D));
	std::cout << models[0].m_vertexBuffer[0].position << std::endl;

	Vec4 v1(10,10,10,1 );
	//std::cout << "modelview " << MODELVIEW << std::endl;
	//std::cout << PROJECTION*MODELVIEW * v1 << std::endl;

	if(renderer.Initialize("rendertest", 50, 100, WIDTH, HEIGHT))
	{
		renderer.SetUpdateCallback(&Update);
		renderer.SetRenderCallback(&Render);
		renderer.MainLoop();
		renderer.CleanUp();
	}
}
