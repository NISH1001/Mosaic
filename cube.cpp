#include <pixel.h>
#include <Line.h>
#include <Circle.h>
#include <Polygon.h>
#include <Transform.h>
#include <Point2D.h>
#include <Matrix.h>

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

	Vec3 v1(0,0,10);
	Vec3 v2(10,0,10);
	Vec3 v3(10,10,10);
	Vec3 v4(0,10,10);
	Vec3 v5(0,0,0);
	Vec3 v6(10,0,0);
	Vec3 v7(10,10,0);
	Vec3 v8(0,10,0);

	double nx=20, ny=0, nz=20;

	ColorRGBA red(255,0,0,255);
	ColorRGBA blue(0,0,255,255);
	ColorRGBA green(0,255,0,255);
	ColorRGBA cyan(0,255,255,255);

	

	Vec3 N = getUnitVector(Vec3(20,0,20));

	Vec3 V(0,1,0);

	Vec3 U(0,0,0);
	U = getUnitVector(crossProduct(N,V));

	V = crossProduct(N,U);

	Mat4 view = getViewMatrix(U,V,N);

	Mat4 trans = Transform::Translate(Vec3(-20,0,-20));

	float zvp = 300;
	float zprp = -40;
	float d = zprp - zvp;
	Mat4 project;
	project[2][2] = -zvp/d;
	project[2][3] = zvp*(zprp/d);
	project[3][2] = -1/d;
	project[3][3] = zprp/d;

	/*
	double angle = 0;
	view = trans = Mat::Mat4();
	project = getIsometricRotation(Mat::Vec3(10,10,10));
	*/
	//std::cout << project << std::endl;
	//std::cout << "ulala: \n" << project*view*trans<<std::endl;
	float angle = 0;

	while(!quit)
	{

		Mat4 rot = Transform::RotateY(angle);

		Vec4 res1 = project*view*rot*trans*Vec4(v1);
		Vec4 res2 = project*view*rot*trans*Vec4(v2);
		Vec4 res3 = project*view*rot*trans*Vec4(v3);
		Vec4 res4 = project*view*rot*trans*Vec4(v4);

		Vec4 res5 = project*view*rot*trans*Vec4(v5);
		Vec4 res6 = project*view*rot*trans*Vec4(v6);
		Vec4 res7 = project*view*rot*trans*Vec4(v7);
		Vec4 res8 = project*view*rot*trans*Vec4(v8);

		/*
		Matrix res5 = project*view*rot*trans*Mat::Vec4(v5,1);
		Matrix res6 = project*view*rot*trans*Mat::Vec4(v6,1);
		Matrix res7 = project*view*rot*trans*Mat::Vec4(v7,1);
		Matrix res8 = project*view*rot*trans*Mat::Vec4(v8,1);
		*/

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

		/*
		res1 = res1/res1.w;
		res2 = res2/res2.w;
		res3 = res3/res3.w;
		res4 = res4/res4.w;
		res5 = res5/res5.w;
		res6 = res6/res6.w;
		res7 = res7/res7.w;
		res8 = res8/res8.w;
		*/

		Point2D p1(res1.x/res1.w, res1.y/res1.w);
		Point2D p2(res2.x/res2.w, res2.y/res2.w);
		Point2D p3(res3.x/res3.w, res3.y/res3.w);
		Point2D p4(res4.x/res4.w, res4.y/res4.w);
		Point2D p5(res5.x/res5.w, res5.y/res5.w);
		Point2D p6(res6.x/res6.w, res6.y/res6.w);
		Point2D p7(res7.x/res7.w, res7.y/res7.w);
		Point2D p8(res8.x/res8.w, res8.y/res8.w);

		Polygon face1(renderer, T(p1), T(p2), T(p3), T(p4), ColorRGBA(255,0,0,0));
		face1.Draw();
		Polygon face2(renderer, T(p2), T(p3), T(p7), T(p6), ColorRGBA(0,255,0,0));
		face2.Draw();
		Polygon face3(renderer, T(p1), T(p5), T(p8), T(p4), ColorRGBA(0,255,0,0));
		face3.Draw();
		Polygon face4(renderer, T(p4), T(p3), T(p7), T(p8), ColorRGBA(0,255,0,0));
		face4.Draw();
		Polygon face5(renderer, T(p1), T(p2), T(p6), T(p5), ColorRGBA(0,255,0,0));
		face5.Draw();
		Polygon face6(renderer, T(p5), T(p6), T(p7), T(p8), ColorRGBA(0,255,0,0));
		face6.Draw();

		//Circle(renderer, 400, 300, 100, ColorRGBA(255,0,0,0)).Draw();
	
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;	

}
