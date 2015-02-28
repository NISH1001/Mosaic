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

Vec3 eyepos(-100, 50, 400) ;
Vec3 lookat(0,50,0);

// main renderer
Renderer renderer; 

//camera
Camera cam;

// projection and view matrices
Mat4 PROJECTION;

// models
std::vector<Model> models;

//lights
AmbientLight ambientlight = {{0.4,0.4,0.4}};
std::vector<DirectedLight> lights = {
                                    {Vec3(0,-1,1), Vec3(1,1,1)},
									{Vec3(1,-1,-1), Vec3(1,1,1)},
									{Vec3(-1,-0.5,0.2), Vec3(1,1,1)},
								};

// Fragment shader, receives a point and renders it in framebuffer
void FragmentShader(Point2D& p)
{	
	//get color
	Vec3 color = p.attributes[0];

	//get vertex normal
	//Vec3 normal = p.attributes[1];
	//normal.NormalizeToUnit();
	
	renderer.SetPixel(p.x, p.y, ColorRGBA(color.x,color.y,color.z,255));
}

// Calculation of light
Vec3 CalculateLight(Vertex3D v, Vec3 normal)
{
	
	//Vec3 normal = (rotate * Vec4(v.normal,0.f)).ToVec3();

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

	//v.color = color;
	return color;
}

// vertex shader, receives a vertex and multiplies it with VIEW and projection matrix
Vertex3D VertexShader( const Vertex3D & vertex)
{
	Vertex3D vcopy = vertex;

    Mat4 modelmatrix = *(renderer.m_currentModelMatrix);

	Vec4 norm = modelmatrix * Vec4(vertex.normal, 0.f);
	norm.NormalizeToUnit();
    
    Vertex3D vcop = vertex;
	vcop.position = modelmatrix * vertex.position;

	// calcuate light
	vcopy.color = CalculateLight(vcop, norm.ToVec3());

	Vec4 image = PROJECTION * cam.GetView() * modelmatrix * vcopy.position; 

	return Vertex3D(image, Vec3::NormalizeToUnit(norm.ToVec3()), vcopy.color);
}


Vertex3D FlatShader( const Vertex3D & v)
{
    Vertex3D vcopy = v;
    Mat4 modelmatrix = *(renderer.m_currentModelMatrix);
	vcopy.position = modelmatrix*v.position;
	Vec4 image = PROJECTION * cam.GetView() * modelmatrix*vcopy.position; 
	return Vertex3D(image, vcopy.normal, vcopy.color);
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
		cam.MoveForward(-200 * dt);
	}

	if(keys[SDL_SCANCODE_D])
	{
		cam.MoveSideway(-200*dt);
	}

	if(keys[SDL_SCANCODE_A])
	{
		cam.MoveSideway(200*dt);
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

    //angle += 0.3;
}

Vertex3D ground[] = {
                    Vertex3D(Vec4(-1,0,-0.5,1), Vec3(0,1,0), Vec3(0,0,1)), 
                    Vertex3D(Vec4(1,0,-0.5,1), Vec3(0,1,0), Vec3(0,0,1)), 
                    Vertex3D(Vec4(1,0,0.5,1), Vec3(0,1,0), Vec3(0,0,1)), 
                    Vertex3D(Vec4(-1,0,-0.5,1), Vec3(0,1,0), Vec3(0,0,1)), 
                    Vertex3D(Vec4(1,0,0.5,1), Vec3(0,1,0), Vec3(0,0,1)), 
                    Vertex3D(Vec4(-1,0,0.5,1), Vec3(0,1,0), Vec3(0,0,1)),
                };
int main()
{
	PROJECTION = Transform::Perspective(60.f * 3.141592/180, float(WIDTH)/HEIGHT, 1.f, 1000.f);
	//PROJECTION = Transform::Orthographic(200,-200,200,-200,-200,200); //R,L,T,B,F,N
	cam.SetView(eyepos, lookat);
    
    //this first model is our main model -> other shall be duplicated using this
    //kd -> controls the color of the model
	Model model("objects/tree.obj", &FlatShader, &CalculateLight);
	model.m_material.ka = {0.1,0.1,0.1};
    model.m_material.kd = {0.3,0.8,0.3};
    model.m_material.ks = {0.0,0.0,0.0};
    model.m_material.ns = 20;
    model.AddTransformation(Transform::Scale(5,5,5));
    model.ApplyTransformation();
    
    //bluish model -> assuming all light source as white
    Model model2 = model;
	model2.m_material.ka = {0.1,0.1,0.1};
    model2.m_material.kd = {0.3,0.3,0.8};
    model2.m_material.ks = {0.0,0.0,0.0};
    model2.m_material.ns = 20;
    model2.AddTransformation(Transform::RotateY(90));
    model2.AddTransformation(Transform::Translate(100,0,300));

    //reddish model -> assuimg all light source as white
    Model model3 = model;
	model3.m_material.ka = {0.1,0.1,0.1};
    model3.m_material.kd = {0.8,0.3,0.3};
    model3.m_material.ks = {0.0,0.0,0.0};
    model3.m_material.ns = 20;
    model3.AddTransformation(Transform::Translate(-200,0,-100));

    //whitish teapot -> kd controls the color of model
	Model teapot("objects/teapot.obj", &FlatShader);
	teapot.m_material.ka = {0.1,0.1,0.1};
    teapot.m_material.kd = {0.4,0.4,0.4};
    teapot.m_material.ks = {0.4,0.4,0.4};
    teapot.m_material.ns = 20;
    teapot.AddTransformation(Transform::Scale(20,20,20));
    teapot.AddTransformation(Transform::Translate(200,0,-300));

    // a ground plane -> lyang during rendering
    Model groundplane(ground, sizeof(ground)/sizeof(ground[0]), &FlatShader, &CalculateLight);
	groundplane.m_material.ka = {0.4,0.4,0.4};
    groundplane.m_material.kd = {0.95f,0.65,0.38};
    groundplane.m_material.ks = {0,0,0};
    groundplane.m_material.ns = 20;
    groundplane.Scale(1,1,2);
    groundplane.AddTransformation(Transform::Scale(200,200,200));

    models.push_back(model);
    models.push_back(model2);
    models.push_back(model3);
    models.push_back(teapot);
    //models.push_back(groundplane);

	if(renderer.Initialize("rendertest", 50, 100, WIDTH, HEIGHT))
	{
		renderer.SetUpdateCallback(&Update);
		renderer.SetRenderCallback(&Render);
		renderer.SetKeyboardCallback(&KeyboardHandler);
		renderer.MainLoop();
		renderer.CleanUp();
	}
}
