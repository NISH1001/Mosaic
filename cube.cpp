#include <pixel.h>
#include <Line.h>
#include <Circle.h>
#include <Polygon.h>
#include <Transform.h>
#include <Point2D.h>
#include <Matrix.h>
#include <vector>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;


void drawAxes(SDL_Renderer * r)
{
	ColorRGBA blue(0,0,255,255);
	Line x(r,0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2, blue);
	Line y(r,SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT, blue);
	x.Draw();
	y.Draw();
}

Point2D T(Point2D p)
{
	return Point2D(p.x+SCREEN_WIDTH/2, -p.y+SCREEN_HEIGHT/2);
}


/*----------------------------------------------------------------*/

Vec3 getUnitVector(const Vec3 & mat)
{
	float r = sqrtf(mat.x*mat.x + mat.y*mat.y + mat.z*mat.z);
	return mat/r;
}

Vec3 crossProduct(const Vec3 & a, const Vec3 &b)
{
	return Vec3(
				a.y * b.z - b.y * a.z,
				a.z * b.x - b.z * b.x,
				a.x * b.y - b.x * a.y
				);
}

Mat4 getViewMatrix(const Vec3 & U, const Vec3 & V, const Vec3 & N)
{
	return Mat4(Vec4(U,0), Vec4(V,0), Vec4(N,0), Vec4(0,0,0,1));
}

// for isometric
Mat4 getIsometricRotation( const Vec3 & vec)
{
	Vec3 unitvec = getUnitVector(vec);
	double x = unitvec.x;
	double z = unitvec.y;
	double y = unitvec.z;
	double r = sqrtf(z*z+y*y);
	// now rotate to xz plane by rotation about x axis
	double thetaX = acos(z/r);
	// now in xz plane y = 0, need rotation about y axis
	double thetaY = -asin(x/sqrtf(1+x*x));

	Mat4 mx = Transform::RotateX(thetaX);
	Mat4 my = Transform::RotateY(-thetaY);
	return my*mx;
}


int main()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout<<"cannot initialize"<<std::endl;
		return -1;
	}

	SDL_Window *window =SDL_CreateWindow("circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	
	if(!window)
		return -1;

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer)
	{
		
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	bool quit = false;
	SDL_Event event;

	std::vector<Vec3> cube = {Vec3(0,0,10), Vec3(10,0,10), Vec3(10,10,10), Vec3(0,10,10),
								Vec3(0,0,0), Vec3(10,0,0), Vec3(10,10,0), Vec3(0,10,0) };

	std::vector<Vec4> res;
	res.resize(cube.size());

	double nx=0, ny=1, nz=5;

	ColorRGBA red(255,0,0,255);
	ColorRGBA blue(0,0,255,255);
	ColorRGBA green(0,255,0,255);
	ColorRGBA cyan(0,255,255,255);

	

	Vec3 N = getUnitVector(Vec3(nx,ny,nz));

	Vec3 V(0,1,0);

	Vec3 U;
	U = getUnitVector(crossProduct(N,V));

	V = crossProduct(N,U);

	Mat4 view = getViewMatrix(U,V,N);

	Mat4 trans = Transform::Translate(Vec3(-nx,-ny,-nz));

	float zvp = 200;
	float zprp = -40;
	float d = zprp - zvp;
	Mat4 project;
	project[2][2] = -zvp/d;
	project[2][3] = zvp*(zprp/d);
	project[3][2] = -1/d;
	project[3][3] = zprp/d;
	//std::cout << project << std::endl;
	/*
	double angle = 0;
	view = trans = Mat::Mat4();
	project = getIsometricRotation(Mat::Vec3(10,10,10));
	*/
	float angle = 0;

	//Mat4 rot;
	//std::cout << rot << std::endl;

	std::vector<Point2D> points(cube.size());

	while(!quit)
	{
		Mat4 rot = Transform::RotateY(angle);
		Mat4 final = project * view * trans * rot;

		for(int i=0; i<cube.size(); i++)
		{
			res[i] = final * Vec4(cube[i]);
			res[i].NormalizeByW();
			points[i] = Point2D(res[i].x, res[i].y);
		}

		angle += 1;
		

		SDL_WaitEvent(&event);

		switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;

        case SDL_KEYDOWN:
        	switch (event.key.keysym.sym)
        	{
        		case SDLK_ESCAPE:
        			quit = true;
        			break;
        	}
        	break;
        }


		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);


		std::vector<Polygon> face = {
								Polygon(renderer, T(points[0]), T(points[1]), T(points[2]), T(points[3]), red),
								Polygon(renderer, T(points[1]), T(points[2]), T(points[6]), T(points[5]), green),
								Polygon(renderer, T(points[0]), T(points[4]), T(points[7]), T(points[3]), blue),
								Polygon(renderer, T(points[3]), T(points[2]), T(points[6]), T(points[7]), cyan),
								Polygon(renderer, T(points[0]), T(points[1]), T(points[5]), T(points[4]), ColorRGBA(255,255,0,0)),
								Polygon(renderer, T(points[4]), T(points[5]), T(points[6]), T(points[7]), ColorRGBA(255,0,255,0))
							};

		for(int i=0; i<face.size(); i++)
		{
			face[i].Draw();
		}
	
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;	

}
