#include "config.h"

#include "window.h"

namespace DISPLAY
{
	Window::Window() : window(nullptr), width(640), height(360)
	{
		glfwInit();
	}

	Window::~Window()
	{
		//Empty
	}

	bool Window::Open()
	{
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
	}

	bool Window::Close()
	{
		glfwSetWindowShouldClose(this->window, true);
		glfwTerminate();
		return 0;
	}

	const bool Window::IsOpen()
	{
		return !glfwWindowShouldClose(this->window);
	}

	bool Window::ProcessInput(int32 key)
	{
		return (glfwGetKey(this->window, key) == GLFW_PRESS);
	}

	void Window::Update()
	{
		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}
}