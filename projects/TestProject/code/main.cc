#include "config.h"

#include <iostream>
#include "gameApp.h"

/*
* TODO Today:
*	- Make a ShaderLoader.
* 
* Future TODO:
*	- Make a Square and then a Cube.
*	- Make a Sphere
*	- Create an OBJ Loader
*	- Create an GLTF Loader
*/

int main()
{
	Game::TestApp testApp;

	if (testApp.Open())
	{
		testApp.Run();
	}

	testApp.Close();

	return 0;
}