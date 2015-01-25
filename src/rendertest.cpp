#include <iostream>
#include <Renderer.h>
#include <Matrix.h>
#include <Transform.h>
#include <Rasterizer.h>
#include <Model.h>

int WIDTH = 800;
int HEIGHT = 600;

//test angle
float angle = 0.f;


// main renderer
Renderer renderer; 

/*make sure it is multiple of 3
	position,normal,color
*/

// OUR LONG AWAITED CUBE
// vertices
Vec3 v1(1,0,1), vc1(255,0,0);
Vec3 v2(1,0,0), vc2(0,255,0);
Vec3 v3(0,0,0), vc3(0,0,255);
Vec3 v4(0,0,1), vc4(255,255,0);
Vec3 v5(1,1,1), vc5(0,255,255);
Vec3 v6(1,1,0), vc6(255,0,255);
Vec3 v7(0,1,0), vc7(0,120,55);
Vec3 v8(0,1,1), vc8(55,255,0);
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
	angle += 100*dt;
	//std::cout << dt << std::endl;
}

// Fragment shader, receives a point and renders it in framebuffer
void FragmentShader(Point2D& p)
{	
	//get color
	Vec3 color = p.attributes[0];

	//get vertex normal
	Vec3 normal = p.attributes[1];
	normal.NormalizeToUnit();
	
	//light vector	
    Vec3 light(200, 100,100);
    light.NormalizeToUnit();
    float intensity = Helper::Min(Helper::Max(Vec3::Dot(normal, light*(-1)), 0.0f) + 0.3f, 1.0f );
    color = color * intensity ;
	
	renderer.SetPixel(p.x, p.y, ColorRGBA(color.x,color.y,color.z,255));
}


Mat4 SCALE = Transform::Scale(Vec3(50,50,50), Vec3(0,0,0));
// projection and view matrices
Mat4 PROJECTION, MODELVIEW, TRANS;

// vertex shader, receives a vertex and multiplies it with modelview and projection matrix
Vertex3D VertexShader(Vertex3D vertex)
{
	Mat4 rotate = Transform::RotateY(angle);
	Vec4 image = TRANS * rotate *
					SCALE * vertex.position;
	//image.NormalizeByW();
	Vec4 normal =  MODELVIEW * rotate * Vec4(vertex.normal, 1.0f);
	return Vertex3D(image, normal.ToVec3(), vertex.color);
}


inline void Render()
{
	renderer.DrawModels(models, &VertexShader, &FragmentShader);
}


int main()
{
	//PROJECTION = Transform::Perspective(90.f * 3.141592/180, float(WIDTH)/HEIGHT, 100.f, 800.f);
	PROJECTION = Transform::Orthographic(200,-200,200,-200,-200,200); //R,L,T,B,F,N
	MODELVIEW = Transform::LookAt(Vec3(0, 50, 150), Vec3(0,0,0));
	TRANS = PROJECTION * MODELVIEW;

	//models.push_back(Model(verticesCube, numCube));
	models.push_back(Model("cube.obj"));

	if(renderer.Initialize("rendertest", 50, 100, WIDTH, HEIGHT))
	{
		renderer.SetUpdateCallback(&Update);
		renderer.SetRenderCallback(&Render);
		renderer.MainLoop();
		renderer.CleanUp();
	}
}
