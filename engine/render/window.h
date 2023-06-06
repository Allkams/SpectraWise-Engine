#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

namespace DISPLAY
{
	class Window
	{
	public:
		Window();
		~Window();

		bool Open();
		bool Close();
		const bool IsOpen();

		void Update();

		bool ProcessInput(int32 key);

	private:
		int32 width;
		int32 height;
		GLFWwindow* window;
	};
}