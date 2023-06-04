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

	private:
		int width;
		int height;
		GLFWwindow* window;
	};
}