#include <pixel.h>
#include <Line.h>
#include <Circle.h>
#include <Polygon.h>
#include <Transform.h>
#include <Point2D.h>
#include <Matrix.h>
#include <Mat.h>

#define WIDTH 1000
#define HEIGHT 800
#define X(x) x+WIDTH/2
#define Y(y) -y+HEIGHT/2

// the vectors U, V, N
double N[] = {0.f,0.f,0.f};
double U[] = {0.f,0.f,0.f};
double V[] = {0.f,0.f,0.f};

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

using namespace Transform;

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window =SDL_CreateWindow("transform", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);


	ColorRGBA red(255,0,0,255);
	ColorRGBA color(123,123,123,255);

	Matrix v1 = Mat::Vec4(0,0,1,1);
	Matrix v2 = Mat::Vec4(1,0,1,1);
	Matrix v3 = Mat::Vec4(1,1,1,1);
	Matrix v4 = Mat::Vec4(0,1,1,1);

	setNvector(0,0,10);
		
	SDL_RenderPresent(renderer);

	SDL_Delay(2000);
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
	norm = Mat::Vec4(x,y,z,1);
	// normalize
	double r = sqrtf(x*x+y*y+z*z);
	N[0] = x/r;
	N[1] = y/r;
	N[2] = z/r;
}

void setUvector()
{
	// first assuming V vector to be (0,1,0)
	// U = V X N
	// assuming V=(0,1,0)
	V[0] = 0;
	V[1] = 1;
	V[2] = 0;

	U[0] = V[1]*N[2] - N[1]*V[2];
	U[1] = V[2]*N[0] - N[2]*V[0];
	U[2] = V[0]*N[1] - V[1]*N[0];
	// normalize
	double r = sqrtf(U[0]*U[0] + U[1]*U[1] + U[2]*U[2]);
	U[0] /= r;
	U[1] /= r;
	U[2] /= r;
}

void setVvector()
{
	// U and N are calculated by this time
	V[0] = -N[1]*U[2] + U[1]*N[2];
	V[1] = -N[2]*U[0] + U[2]*N[0];
	V[2] = -N[0]*U[1] + U[1]*N[0];
}

void setTranslationMatrix(double x, double y, double z)
{
	trans[0][3] = x;
	trans[1][3] = y;
	trans[2][3] = z;
}

void setRotationMatrix()
{
	rot[0][0] = U[0];
	rot[0][1] = U[1];
	rot[0][2] = U[2];

	rot[1][0] = V[0];
	rot[1][1] = V[1];
	rot[1][2] = V[2];

	rot[2][0] = N[0];
	rot[2][1] = N[1];
	rot[2][2] = N[2];
}

void setProjectionMatrix(double zvp)
{
	Matrix temp = rot*trans*norm;// obtaining the normal after translating and rotating in WC
	double zprp = temp[2][0];
	double d = zprp - zvp; // as in book

	project[2][2] = -zvp/d;
	project[2][3] = zvp*(zprp/d);
	project[2][3] = -1/d;
	project[3][3] = zprp/d;
}
	
