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

	Matrix v1 = Mat::Vec4(0,0,10,1);
	Matrix v2 = Mat::Vec4(10,0,10,1);
	Matrix v3 = Mat::Vec4(10,10,10,1);
	Matrix v4 = Mat::Vec4(0,10,10,1);
	Matrix v5 = Mat::Vec4(0,0,0,1);
	Matrix v6 = Mat::Vec4(10,0,0,1);
	Matrix v7 = Mat::Vec4(10,10,0,1);
	Matrix v8 = Mat::Vec4(0,10,0,1);

	double nx=20, ny=0, nz=20;
	Matrix trans = Transform::Translate(Mat::Vec3(nx,ny,nz));
	Matrix sc = Transform::Scale(Mat::Vec3(1,2,3), Mat::Vec3(4,5,6));
	Matrix sc1 = Transform::Scale(1,2,3, Mat::Vec3(4,5,6));
	Matrix rot = Transform::RotateZ(60);
	std::cout << sc1 << std::endl;

	Matrix N = getUnitVector(Mat::Vec3(20,0,20));
	std::cout <<N << std::endl;

	Matrix V = Mat::Vec3(0,1,0);

	Matrix U = Mat::Vec3(0,0,0);
	U = getUnitVector(crossProduct(N,V));
	std::cout << U << std::endl;

	V = crossProduct(N,U);
	std::cout << V << std::endl;

	while(!quit)
	{
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


		drawAxes(renderer);
		//Circle(renderer, 400, 300, 100, ColorRGBA(255,0,0,0)).Draw();
	
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;	

}