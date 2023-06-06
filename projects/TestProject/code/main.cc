#include "config.h"
#include <iostream>
#include "gameApp.h"

/*
* TODO:
*	- Make Triangle
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