#include <pixel.h>
#include <Line.h>
#include <Circle.h>
#include <Triangle.h>
#include <Transform.h>
#include <Point2D.h>
#include <Matrix.h>
#include <Mat.h>

#define WIDTH 1000
#define HEIGHT 800
#define X(x) x+WIDTH/2
#define Y(y) -y+HEIGHT/2


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

	Matrix mat1 = Mat::Vec2(1,2);
	Matrix mat2 = Mat::Vec2(1,2);
	Matrix mat = (Mat::Mat3() * Mat::Vec3(mat1,1) + Mat::Vec3(mat2,0));

	for(int i=0; i<mat.rows; i++)
	{
		for(int j=0; j<mat.cols; j++)
		{
			std::cout << mat[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
	
	drawAxes(renderer);

	ColorRGBA red(255,0,0,255);
	ColorRGBA color(123,123,123,255);
		
	Point2D p1(100, 100);
	Point2D p2(200, 200);
	Point2D p3(210, 100);

	Triangle t(renderer, T(p1), T(p2), T(p3), color);
	t.DrawFilled();
	
	//Triangle(renderer, T(translate(p1, 50, -50)), T(translate(p2, 50, -50)), T(translate(p3, 50, -50)), red);
	//Triangle(renderer,T(rotate(p1, 100,100, 30)),T(rotate(p2, 100,100, 30)),T(rotate(p3, 100,100, 30)), red);
	//Triangle(renderer,T(scale(p1, 0,0, 2,2)),T(scale(p2, 0,0, 2,2)),T(scale(p3, 0,0, 2,2)), red);
	//Triangle(renderer,T(reflect(p1,-2,1)),T(reflect(p2,-2,1)),T(reflect(p3,-2, 1)), GREEN);


	SDL_RenderPresent(renderer);

	SDL_Delay(2000);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
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
	
/*void Triangle(SDL_Renderer* r,Point2D p1, Point2D p2, Point2D p3, ColorRGBA color)
{
	Line(r, p1, p2, color).Draw();;
	Line(r, p2,p3, color).Draw();
	Line(r, p3, p1, color).Draw();
}
	
*/
