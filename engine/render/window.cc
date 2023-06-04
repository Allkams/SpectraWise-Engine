#include "config.h"

#include "window.h"

namespace DISPLAY
{
	Window::Window() : window(nullptr), width(640), height(360)
	{

	}

	Window::~Window()
	{

	}

	bool Window::Open()
	{
		//Problem here!
		this->window = glfwCreateWindow(this->width, this->height, "Spectrawise-Engine", NULL, NULL);

		if (this->window == nullptr)
		{
			printf("[ WINDOW ] : Failed to create GLFW Window! \n");
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(this->window);

		glViewport(0, 0, this->width, this->height);

		return true;

		//Move to update function
		while (!glfwWindowShouldClose(this->window))
		{
			glfwSwapBuffers(this->window);
			glfwPollEvents();
		}
		//-------------------------------------------------
	}
}