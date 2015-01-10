#include <pixel.h>
#include <Line.h>
#include <Circle.h>
#include <Polygon.h>
#include <Point2D.h>
#include <Matrix.h>
#include <Mat.h>

#define WIDTH 1000
#define HEIGHT 800
#define X(x) x+WIDTH/2
#define Y(y) -y+HEIGHT/2

// the vectors U, V, N
Matrix N = Mat::Vec3(0,0,0);
Matrix V = Mat::Vec3(0,1,0);
Matrix U = Mat::Vec3(0,0,0);

// the normal Vector
Matrix norm; 

// the matrices
Matrix trans = Mat::Mat4(); //for translation of VC origin to WC origin
Matrix rot = Mat::Mat4(); // for aligning x,y,z axes to u, v, n
Matrix project = Mat::Mat4(); // for perspective projection

// matrix manipulation functions
void setNvector(double, double, double); // assuming look at is at (0,0,0)
void setUvector(); // after getting N vector
void setVvector(); // after getting N and U vectors
void setTranslationMatrix(double, double, double); // set trans matrix
void setRotationMatrix(); // set the rot matrix
void setProjectionMatrix(double z); // sets the matrix project corresponding to projection plane at z

void drawAxes(SDL_Renderer*r);
Point2D T(Point2D);
//void Triangle(SDL_Renderer* r,Point2D p1, Point2D p2, Point2D p3, ColorRGBA color);

//using namespace Transform;

int main()
{
	
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window =SDL_CreateWindow("transform", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	ColorRGBA red(255,0,0,255);
	ColorRGBA color(123,123,123,255);

	drawAxes(renderer);

	Matrix v1 = Mat::Vec4(0,0,10,1);
	Matrix v2 = Mat::Vec4(10,0,10,1);
	Matrix v3 = Mat::Vec4(10,10,10,1);
	Matrix v4 = Mat::Vec4(0,10,10,1);
	Matrix v5 = Mat::Vec4(0,0,0,1);
	Matrix v6 = Mat::Vec4(10,0,0,1);
	Matrix v7 = Mat::Vec4(10,10,0,1);
	Matrix v8 = Mat::Vec4(0,10,0,1);

	int nx=20,ny=0,nz=20;
	bool quit = false;
	Matrix res1, res2, res3, res4;
	SDL_Event event;

	setNvector(nx,ny,nz);
	setUvector();
	setVvector();

	setRotationMatrix();
	setProjectionMatrix(200); 

	while(!quit)
	{
		
	res1 = project*rot*trans*v5;
	res2 = project*rot*trans*v6;
	res3 = project*rot*trans*v7;
	res4 = project*rot*trans*v8;

	Point2D p5(res1[0][0]/res1[3][0], res1[1][0]/res1[3][0]);
	Point2D p6(res2[0][0]/res2[3][0], res2[1][0]/res2[3][0]);
	Point2D p7(res3[0][0]/res3[3][0], res3[1][0]/res3[3][0]);
	Point2D p8(res4[0][0]/res4[3][0], res4[1][0]/res4[3][0]);

	Polygon pp(renderer, T(p5), T(p6), T(p7), T(p8), color);
	pp.DrawFilled();

	res1 = project*rot*trans*v1;
	res2 = project*rot*trans*v2;
	res3 = project*rot*trans*v3;
	res4 = project*rot*trans*v4;

	Point2D p1(res1[0][0]/res1[3][0], res1[1][0]/res1[3][0]);
	Point2D p2(res2[0][0]/res2[3][0], res2[1][0]/res2[3][0]);
	Point2D p3(res3[0][0]/res3[3][0], res3[1][0]/res3[3][0]);
	Point2D p4(res4[0][0]/res4[3][0], res4[1][0]/res4[3][0]);

	Polygon p(renderer, T(p1), T(p2), T(p3), T(p4), red);
	p.DrawFilled();

	SDL_RenderDrawPoint(renderer, 100, 100);


	SDL_RenderPresent(renderer);

	SDL_WaitEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
				case SDLK_LEFT: nx-=5;break;
				case SDLK_RIGHT: nx+=5;break;
				case SDLK_UP : ny+=5;break;
				case SDLK_DOWN: ny-=5;break;
				case SDLK_w:nz+=5;break;
				case SDLK_s:nz-=5;break;
			}
			setNvector(nx,ny,nz);
			setUvector();
			setVvector();

			setRotationMatrix();
			setProjectionMatrix(200); 
			SDL_SetRenderDrawColor(renderer, 255,255,255,255);
			SDL_RenderClear(renderer);
			break;
	}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}


void drawAxes(SDL_Renderer * r)
{
	ColorRGBA blue(0,0,255,255);
	Line x(r,0, HEIGHT/2, WIDTH, HEIGHT/2, blue);
	Line y(r,WIDTH/2, 0, WIDTH/2, HEIGHT, blue);
	x.Draw();
	y.Draw();
}

Point2D T(Point2D p)
{
	return Point2D(p.x+WIDTH/2, -p.y+HEIGHT/2);
}
	
void setNvector(double x, double y, double z)
{
	setTranslationMatrix(-x,-y,-z);

	norm = Mat::Vec4(-x,-y,-z,1);
	// normalize
	double r = sqrtf(x*x+y*y+z*z);
	N[0][0] = x/r;
	N[1][0] = y/r;
	N[2][0] = z/r;
	std::cout << "Normal\n" << N << std::endl;
}

void setUvector()
{
	// first assuming V vector to be (0,1,0)
	// U = V X N
	// assuming V=(0,1,0)
	double a, b, c;
	std::cout << "initial V\n" << V << std::endl;

	a = U[0][0] = V[1][0]*N[2][0] - N[1][0]*V[2][0];
	b = U[1][0] = V[2][0]*N[0][0] - N[2][0]*V[0][0];
	c = U[2][0] = V[0][0]*N[1][0] - V[1][0]*N[0][0];

	std::cout << "initial U\n" << U << std::endl;
	// normalize
	double r = sqrtf(a*a+b*b+c*c);
	U[0][0] /= r;
	U[1][0] /= r;
	U[2][0] /= r;

	std::cout << "normalized U\n" << U << std::endl;
}

void setVvector()
{
	// U and N are calculated by this time
	V[0][0] = N[1][0]*U[2][0] - U[1][0]*N[2][0];
	V[1][0] = N[2][0]*U[0][0] - U[2][0]*N[0][0];
	V[2][0] = -N[0][0]*U[1][0] + U[0][0]*N[1][0];

	std::cout << "Normalized V\n" << V <<  std::endl;
}

void setTranslationMatrix(double x, double y, double z)
{
	trans[0][3] = x;
	trans[1][3] = y;
	trans[2][3] = z;
	std::cout << "translation\n" << trans << std::endl;
}

void setRotationMatrix()
{
	rot[0][0] = U[0][0];
	rot[0][1] = U[1][0];
	rot[0][2] = U[2][0];

	rot[1][0] = V[0][0];
	rot[1][1] = V[1][0];
	rot[1][2] = V[2][0];

	rot[2][0] = N[0][0];
	rot[2][1] = N[1][0];
	rot[2][2] = N[2][0];
	
	std::cout << "rotation\n";
	std::cout << rot << std::endl;
}

void setProjectionMatrix(double zvp)
{
	Matrix temp = rot*trans*norm;// obtaining the normal after translating and rotating in WC
	double zprp = temp[2][0]; // this is origin. of the viewing coordinate
	std::cout << "zvp: " << zvp << std::endl;
	double d = zprp - zvp; // as in book

	project[2][2] = -zvp/d;
	std::cout << "zprp: " << zprp << std::endl;
	project[2][3] = zvp*(zprp/d);
	project[3][2] = -1/d;
	project[3][3] = zprp/d;

	std::cout << "projection\n" << project << std::endl;
}
	
