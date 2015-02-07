#include <iostream>
#include <Renderer.h>
#include <Matrix.h>
#include <Transform.h>
#include <Rasterizer.h>
#include <Model.h>
#include <Camera.h>
#include <Light.h>
#include <Material.h>

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

//lights
AmbientLight ambientlight = {{0.4,0.4,0.4}};
std::vector<DirectedLight> lights = {
									{Vec3(1,-1,-1), Vec3(0,0,1)},
									{Vec3(-1,-0.5,0.2), Vec3(1,0,0)},
								};

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

// inplace Calculation of light
void CalculateLight(Vertex3D& v, Vec3 normal)
{
	//our color intensity 0 - 1 range
	Vec3 intensity;

	//calculate ambient intensity
	intensity.x = ambientlight.intensity.x * renderer.m_currentMaterial->ka.x;
	intensity.y = ambientlight.intensity.y * renderer.m_currentMaterial->ka.y;
	intensity.z = ambientlight.intensity.z * renderer.m_currentMaterial->ka.z;

	//our view vector from vertex to camera in world space
	Vec3 view = cam.GetPos() - v.position.ToVec3();
	view.NormalizeToUnit();

	for(unsigned i=0; i<lights.size(); ++i)
	{
		//calculate diffuse intensity
		float diffintensity = Vec3::Dot(normal, lights[i].direction);
		diffintensity = Helper::Max(diffintensity, 0.f);
		diffintensity = Helper::Min(diffintensity,1.f);

		intensity.x += lights[i].intensity.x * renderer.m_currentMaterial->kd.x*diffintensity;
		intensity.y += lights[i].intensity.y * renderer.m_currentMaterial->kd.y*diffintensity;
		intensity.z += lights[i].intensity.z * renderer.m_currentMaterial->kd.z*diffintensity;

		/*
			SPECULAR ...
			get our vector from vertex to eye
			it may or maynot be in the direction of reflected ray
			so has to calculate specular intensity using
			this view vector and reflected vector
		*/

		Vec3 reflected = lights[i].direction - normal * Vec3::Dot(normal, lights[i].direction) * 2;
		reflected.NormalizeToUnit();

		float specularfactor = Vec3::Dot(reflected, view);
		specularfactor = Helper::Max(specularfactor,0.0f);
		specularfactor = Helper::Min(specularfactor, 1.0f);

		float dampfactor = pow(specularfactor, renderer.m_currentMaterial->ns);

		intensity.x += lights[i].intensity.x * renderer.m_currentMaterial->ks.x * dampfactor;
		intensity.y += lights[i].intensity.y * renderer.m_currentMaterial->ks.y * dampfactor;
		intensity.z += lights[i].intensity.z * renderer.m_currentMaterial->ks.z * dampfactor;
	}	
	
	//clamp the values
	intensity.x = Helper::Min(intensity.x, 1.0f);
	intensity.y = Helper::Min(intensity.y, 1.0f);
	intensity.z = Helper::Min(intensity.z, 1.0f);

	//finally get our 0-255 RGB value
	Vec3 color;
	color.x = intensity.x * 255;
	color.y = intensity.y * 255;
	color.z = intensity.z * 255;

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


	//models.push_back(Model(verticesCube, numCube));
	Model model("teapot.obj");
	model.m_material.ka = {0.1,0.1,0.1};
    model.m_material.kd = {0.5,0.5,0.5};
    model.m_material.ks = {0.5,0.5,0.5};
    model.m_material.ns = 20;

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
