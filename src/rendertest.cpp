#include <iostream>
#include <Renderer.h>

void Update(double dt)
{
	std::cout << dt << std::endl;
}

int main()
{
	Renderer renderer;

	//renderer.Initialize("rendertest", 50, 100, 800, 600);

	if(renderer.Initialize("rendertest", 50, 100, 800, 600))
	{
		renderer.SetUpdateCallback(&Update);
		renderer.MainLoop();
	}

	renderer.CleanUp();
}