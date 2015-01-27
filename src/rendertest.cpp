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

Vec3 eyepos(0, 100, 300);


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
	
	renderer.SetPixel(p.x, p.y, ColorRGBA(color.x,color.y,color.z,255));
}


Mat4 SCALE = Transform::Scale(Vec3(30,30,30), Vec3(0,0,0));
// projection and view matrices
Mat4 PROJECTION, MODELVIEW, TRANS;

// vertex shader, receives a vertex and multiplies it with modelview and projection matrix
Vertex3D VertexShader(Vertex3D vertex)
{
	Mat4 rotate = Transform::RotateY(angle);
	Vec4 image = TRANS* rotate *SCALE*
					 vertex.position;

	Vec4 normal =  rotate * Vec4(vertex.normal, 0.0f);
	Vec3 n = Vec3::NormalizeToUnit(normal.ToVec3());

	// assuming color of the object is white i.e has reflectivity (1,1,1)
	float refred=1.f, refgreen=1.f, refblue=1.f;
	// light1 has color blue(0,0,255), direction (1,0,-1.5)
	// light2 has color red(255,0,0), direction (-1,0,-1.5)
	Vec3 l2(255,0,0), l1(0,0,255);
	Vec3 d2(-1,-0.5,0.2), d1(1,0,0.2);
	// first normalize light directions, these can be precalculated for better efficiency, can be made global
	d1.NormalizeToUnit();
	d2.NormalizeToUnit();
	// intensities
	float i1 = Vec3::Dot(n,d1), i2 = Vec3::Dot(n,d2);
	Vec3 color = Vec3(Helper::Max((l1.x*i1+l2.x*i2)*refred/2.f,0.f), 
				 	  Helper::Max((l1.y*i1+l2.y*i2)*refgreen/2.f,0.f), 
				 	  Helper::Max((l1.z*i1+l2.z*i2)*refblue/2.f,0.f)); 
	//color.NormalizeToUnit();
	/*
	Vec3 color = Vec3(255,255,255);
	Vec3 light(-1,-1,0);
	light.NormalizeToUnit();
	float intensity = Vec3::Dot(n,light);
	color = Vec3(Helper::Max(color.x*intensity*refred,0.f), Helper::Max(color.y*intensity*refgreen,0.f), Helper::Max(color.z*intensity*refblue,0.f));
	*/

	//out light for specular
	Vec3 light(0,0,255);
	Vec3 lightdir(1,-1,-1);
	lightdir.NormalizeToUnit();

	//get worldspace vertex
	Vec3 vertexpos = (rotate * SCALE * vertex.position).ToVec3();

	/*get our vector from vertex to eye
		it may or maynot be in the direction of reflected ray
		so has to calculate specular intensity using
		this view vector and reflected vector
	*/
	Vec3 view = eyepos - vertexpos;
	view.NormalizeToUnit();

	//calculate the reflected vector
	Vec3 reflected = lightdir - n * Vec3::Dot(n, lightdir);
	reflected.NormalizeToUnit();

	//now calculate our specular factor
	float specularfactor = Vec3::Dot(reflected, view);
	specularfactor = Helper::Max(specularfactor,0.0f);

	//damping factor for specular
	//greater damping factor = low specular and ...
	float dampfactor = pow(specularfactor, 0.4);

	Vec3 finalspecular = light * dampfactor;

	color += finalspecular;

	return Vertex3D(image, Vec3::NormalizeToUnit(normal.ToVec3()), color);
}


inline void Render()
{
	renderer.DrawModels(models, &VertexShader, &FragmentShader);
}

int main()
{
	PROJECTION = Transform::Perspective(60.f * 3.141592/180, float(WIDTH)/HEIGHT, 100.f, 1000.f);
	//PROJECTION = Transform::Orthographic(200,-200,200,-200,-200,200); //R,L,T,B,F,N
	MODELVIEW = Transform::LookAt(eyepos, Vec3(0,0,0));
	TRANS = PROJECTION * MODELVIEW;

	Model model("cone.obj");

	for(unsigned i=0; i<model.m_vertexBuffer.size(); ++i)
		model.m_vertexBuffer[i].position = Transform::Translate(3,0,0) * 
											model.m_vertexBuffer[i].position;

	//models.push_back(Model(verticesCube, numCube));
	models.push_back(Model("teapot.obj"));
	models.push_back(model);

	if(renderer.Initialize("rendertest", 50, 100, WIDTH, HEIGHT, MODELVIEW))
	{
		renderer.SetUpdateCallback(&Update);
		renderer.SetRenderCallback(&Render);
		renderer.MainLoop();
		renderer.CleanUp();
	}
}
