#pragma once

#include "render/window.h"

/*
* TODO:
*	- Add functions for ImGui
*	- Add functions for NanoVG
*/

namespace Game
{
	class TestApp
	{
	public:
		TestApp();
		~TestApp();

		bool Open();

		bool Run();

		bool Close();

	private:
		DISPLAY::Window* window;
	};
}
