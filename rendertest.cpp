#include <iostream>
#include <Renderer.h>

int main()
{
	Renderer renderer;

	//renderer.Initialize("rendertest", 50, 100, 800, 600);

	if(renderer.Initialize("rendertest", 50, 100, 800, 600))
		renderer.MainLoop();

	renderer.CleanUp();
}