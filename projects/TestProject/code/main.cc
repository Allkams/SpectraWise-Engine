#include "config.h"
#include <iostream>
#include "render/window.h"

int main()
{


	std::cout << "Hello OpenGL!" << std::endl;

	DISPLAY::Window* window = new DISPLAY::Window;
	/*if (window->Open())
	{
		printf("Window up and running!");
	}*/

	return 0;
}