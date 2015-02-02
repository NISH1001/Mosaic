#include <iostream>
#include <Renderer.h>
#include <Matrix.h>
#include <Transform.h>
#include <Rasterizer.h>
#include <Model.h>
#include <Camera.h>

int WIDTH = 800;
int HEIGHT = 600;

//test angle
float angle = 0.f;

Vec3 eyepos(0, 50, 200) ;
Vec3 lookat(0,50,0);

// main renderer
Renderer renderer; 

//camera
Camera cam;

Mat4 SCALE = Transform::Scale(Vec3(30,30,30), Vec3(0,0,0));
// projection and view matrices
Mat4 PROJECTION, VIEW;

// models
std::vector<Model> models;

/*make sure it is multiple of 3
	position,normal,color
*/

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

// Calculation of light
void CalculateLight(Vertex3D& v, Vec3 normal)
{
	// assuming color of the object is white i.e has reflectivity (1,1,1)
	float refred=1.f, refgreen=1.f, refblue=1.f;

	Vec3 l2(255,0,0), l1(0,0,255);
	Vec3 d2(-1,-0.5,0.2), d1(1,0,0.2);

	// first normalize light directions, these can be precalculated for better efficiency, can be made global
	d1.NormalizeToUnit();
	d2.NormalizeToUnit();

	// intensities
	float i1 = Vec3::Dot(normal,d1), i2 = Vec3::Dot(normal,d2);

	Vec3 color = Vec3(Helper::Max((l1.x*i1+l2.x*i2)*refred/2.f,0.f), 
				 	  Helper::Max((l1.y*i1+l2.y*i2)*refgreen/2.f,0.f), 
				 	  Helper::Max((l1.z*i1+l2.z*i2)*refblue/2.f,0.f)); 

	//out light for specular
	Vec3 light(0,0,255);
	Vec3 lightdir(1,-1,-1);
	lightdir.NormalizeToUnit();

	/*get our vector from vertex to eye
		it may or maynot be in the direction of reflected ray
		so has to calculate specular intensity using
		this view vector and reflected vector
	*/
	Vec3 view = cam.GetPos() - v.position.ToVec3();
	view.NormalizeToUnit();

	//calculate the reflected vector and normalize it.
	Vec3 reflected = lightdir - normal * Vec3::Dot(normal, lightdir) * 2;
	reflected.NormalizeToUnit();

	//now calculate our specular factor
	float specularfactor = Vec3::Dot(reflected, view);
	specularfactor = Helper::Max(specularfactor,0.0f);

	//damping factor for specular
	//greater damping factor = low specular and ...
	float dampfactor = pow(specularfactor, 20);

	Vec3 finalspecular = light * dampfactor;

	//color += finalspecular;
	color = Vec3(Helper::Min(color.x+finalspecular.x,255.f),Helper::Min(color.y+finalspecular.y,255.f),Helper::Min(color.z+finalspecular.z,255.f));

	//v.color = Vec3(100, 0, 0);
	v.color = color;
}

// vertex shader, receives a vertex and multiplies it with VIEW and projection matrix
Vertex3D VertexShader(Vertex3D vertex)
{
	Mat4 rotate = Transform::RotateY(angle);
	Mat4 model = rotate * SCALE;
	vertex.position = model * vertex.position;

	Vec4 norm = rotate * Vec4(vertex.normal, 0.f);
	norm.NormalizeToUnit();

	// calcuate light
	CalculateLight(vertex, norm.ToVec3());

	Vec4 image = PROJECTION * cam.GetView() * 
					 vertex.position;
	return Vertex3D(image, Vec3::NormalizeToUnit(norm.ToVec3()), vertex.color);
}


void FlatShader(Vertex3D v)
{
	
}


inline void Render()
{
	renderer.DrawModels(models, &VertexShader, &FragmentShader);
}

inline void KeyboardHandler(SDL_Event *e)
{

}

void Update(double dt)
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W])
	{
		cam.MoveForward(200*dt);
	}

	if (keys[SDL_SCANCODE_S])
	{
		cam.MoveForward(-250 * dt);
	}

	if(keys[SDL_SCANCODE_D])
	{
		cam.MoveSideway(-250*dt);
	}

	if(keys[SDL_SCANCODE_A])
	{
		cam.MoveSideway(250*dt);
	}

	if(keys[SDL_SCANCODE_RIGHT])
	{
		cam.RotateView(-100*dt);
	}

	if(keys[SDL_SCANCODE_LEFT])
	{
		cam.RotateView(100*dt);
	}

	if(keys[SDL_SCANCODE_UP])
	{
		cam.MoveVertically(100*dt);
	}

	if(keys[SDL_SCANCODE_DOWN])
	{
		cam.MoveVertically(-100*dt);
	}

	//angle += 100*dt;
	
}


int main()
{
	PROJECTION = Transform::Perspective(60.f * 3.141592/180, float(WIDTH)/HEIGHT, 100.f, 1000.f);
	//PROJECTION = Transform::Orthographic(200,-200,200,-200,-200,200); //R,L,T,B,F,N
	cam.SetView(eyepos, lookat);

	Model model("cone.obj");

	for(unsigned i=0; i<model.m_vertexBuffer.size(); ++i)
		model.m_vertexBuffer[i].position = Transform::Translate(4,0,0) * 
											model.m_vertexBuffer[i].position;

	//models.push_back(Model(verticesCube, numCube));
	models.push_back(Model("teapot.obj"));
	models.push_back(model);

	if(renderer.Initialize("rendertest", 50, 100, WIDTH, HEIGHT))
	{
		renderer.SetUpdateCallback(&Update);
		renderer.SetRenderCallback(&Render);
		renderer.SetKeyboardCallback(&KeyboardHandler);
		renderer.MainLoop();
		renderer.CleanUp();
	}
}
