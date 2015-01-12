#include <pixel.h>
#include <Line.h>
#include <Circle.h>
#include <Polygon.h>
#include <Transform.h>
#include <Point2D.h>
#include <Matrix.h>
#include <Mat.h>

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

Matrix getUnitVector(const Matrix & mat)
{
	Matrix res = mat;
	double r=0;
	for(int i=0; i<mat.rows; i++)
	{
		r += mat[i][0]*mat[i][0];
	}
	r = sqrtf(r);

	for(int i=0; i<mat.rows; i++)
	{
		res[i][0] /= r;
	}

	return res;
}

Matrix crossProduct(const Matrix & a, const Matrix &b)
{
	double x = a[1][0]*b[2][0] - b[1][0]*a[2][0];
	double y = a[2][0]*b[0][0] - b[2][0]*a[0][0];
	double z = a[0][0]*b[1][0] - b[1][0]*a[2][0];
	return Mat::Vec3(x,y,z);
}

Matrix getViewMatrix(const Matrix & U, const Matrix & V, const Matrix & N)
{
	Matrix rot = Mat::Mat4();

	rot[0][0] = U[0][0];
	rot[0][1] = U[1][0];
	rot[0][2] = U[2][0];

	rot[1][0] = V[0][0];
	rot[1][1] = V[1][0];
	rot[1][2] = V[2][0];

	rot[2][0] = N[0][0];
	rot[2][1] = N[1][0];
	rot[2][2] = N[2][0];

	return rot;
}

// for isometric
Matrix getIsometricRotation(Matrix vec)
{
	Matrix unitvec = getUnitVector(vec);
	double x = unitvec[0][0];
	double z = unitvec[2][0];
	double y = unitvec[1][0];
	double r = sqrtf(z*z+y*y);
	// now rotate to xz plane by rotation about x axis
	double thetaX = acos(z/r);
	// now in xz plane y = 0, need rotation about y axis
	double thetaY = -asin(x/sqrtf(1+x*x));

	Matrix mx = Transform::RotateX(thetaX);
	Matrix my = Transform::RotateY(-thetaY);
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

	Matrix v1 = Mat::Vec3(0,0,10);
	Matrix v2 = Mat::Vec3(10,0,10);
	Matrix v3 = Mat::Vec3(10,10,10);
	Matrix v4 = Mat::Vec3(0,10,10);
	Matrix v5 = Mat::Vec3(0,0,0);
	Matrix v6 = Mat::Vec3(10,0,0);
	Matrix v7 = Mat::Vec3(10,10,0);
	Matrix v8 = Mat::Vec3(0,10,0);

	double nx=20, ny=0, nz=20;

	ColorRGBA red(255,0,0,255);
	ColorRGBA blue(0,0,255,255);
	ColorRGBA green(0,255,0,255);
	ColorRGBA cyan(0,255,255,255);

	/*
	Matrix trans = Transform::Translate(Mat::Vec3(nx,ny,nz));
	Matrix sc = Transform::Scale(Mat::Vec3(1,2,3), Mat::Vec3(4,5,6));
	Matrix sc1 = Transform::Scale(1,2,3, Mat::Vec3(4,5,6));
	Matrix rot = Transform::RotateZ(60);
	std::cout << sc1 << std::endl;
	*/

	Matrix N = getUnitVector(Mat::Vec3(20,0,20));

	Matrix V = Mat::Vec3(0,1,0);

	Matrix U = Mat::Vec3(0,0,0);
	U = getUnitVector(crossProduct(N,V));

	V = crossProduct(N,U);

	Matrix view = getViewMatrix(U,V,N);

	Matrix trans = Transform::Translate(Mat::Vec3(-20,0,-20));

	double zvp = 100;
	double zprp = 0;
	double d = zprp - zvp;
	Matrix project = Mat::Mat4();
	project[2][2] = -zvp/d;
	project[2][3] = zvp*(zprp/d);
	project[3][2] = -1/d;
	project[3][3] = zprp/d;

	double angle = 0;
	view = trans = Mat::Mat4();
	project = getIsometricRotation(Mat::Vec3(10,10,10));
	std::cout << project;
	std::cout << "ulala: \n" << project*view*trans<<std::endl;

	while(!quit)
	{

		Matrix rot = Transform::RotateX(angle);

		Matrix res1 = project*view*trans*rot*Mat::Vec4(v1,1);
		Matrix res2 = project*view*trans*rot*Mat::Vec4(v2,1);
		Matrix res3 = project*view*trans*rot*Mat::Vec4(v3,1);
		Matrix res4 = project*view*trans*rot*Mat::Vec4(v4,1);

		Matrix res5 = project*view*trans*rot*Mat::Vec4(v5,1);
		Matrix res6 = project*view*trans*rot*Mat::Vec4(v6,1);
		Matrix res7 = project*view*trans*rot*Mat::Vec4(v7,1);
		Matrix res8 = project*view*trans*rot*Mat::Vec4(v8,1);

		/*
		Matrix res5 = project*view*rot*trans*Mat::Vec4(v5,1);
		Matrix res6 = project*view*rot*trans*Mat::Vec4(v6,1);
		Matrix res7 = project*view*rot*trans*Mat::Vec4(v7,1);
		Matrix res8 = project*view*rot*trans*Mat::Vec4(v8,1);
		*/

		//angle += 1;
		

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


		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		Point2D p1(res1[0][0]/res1[3][0]*15, res1[1][0]/res1[3][0]*15);
		Point2D p2(res2[0][0]/res2[3][0]*15, res2[1][0]/res2[3][0]*15);
		Point2D p3(res3[0][0]/res3[3][0]*15, res3[1][0]/res3[3][0]*15);
		Point2D p4(res4[0][0]/res4[3][0]*15, res4[1][0]/res4[3][0]*15);
		Point2D p5(res5[0][0]/res5[3][0]*15, res5[1][0]/res5[3][0]*15);
		Point2D p6(res6[0][0]/res6[3][0]*15, res6[1][0]/res6[3][0]*15);
		Point2D p7(res7[0][0]/res7[3][0]*15, res7[1][0]/res7[3][0]*15);
		Point2D p8(res8[0][0]/res8[3][0]*15, res8[1][0]/res8[3][0]*15);

		Polygon face1(renderer, T(p1), T(p2), T(p3), T(p4), red);
		face1.Draw();
		Polygon face2(renderer, T(p2), T(p3), T(p7), T(p6), cyan);
		face2.Draw();
		Polygon face3(renderer, T(p1), T(p5), T(p8), T(p4), blue);
		face3.Draw();
		Polygon face4(renderer, T(p4), T(p3), T(p7), T(p8), green);
		face4.Draw();
		Polygon face5(renderer, T(p1), T(p2), T(p6), T(p5), red);
		face5.Draw();
		Polygon face6(renderer, T(p5), T(p6), T(p7), T(p7), cyan);
		face6.Draw();


		drawAxes(renderer);
		//Circle(renderer, 400, 300, 100, ColorRGBA(255,0,0,0)).Draw();
	
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;	

}
