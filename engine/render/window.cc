// 
// Copyright 2023 Alexander Marklund (Allkams02@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated
// documentation files(the “Software”), to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the following conditions :
//
// The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN 
// AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
// THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include "config.h"
#include <imgui.h>
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "core/input/inputManager.h"
#include "window.h"

namespace DISPLAY
{
	int32 Window::WindowCount = 0;

	Window::Window() : window(nullptr), width(800), height(600), title("Spectrawise-Engine")
	{
		
	}

	Window::~Window()
	{
		//Empty
	}

	bool Window::Open()
	{

		if (Window::WindowCount == 0)
		{
			if (!glfwInit()) return false;
		}

		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glfwWindowHint(GLFW_RED_BITS, 8);
		glfwWindowHint(GLFW_GREEN_BITS, 8);
		glfwWindowHint(GLFW_BLUE_BITS, 8);
		glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);


		this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(this->window);

		if (this->window != nullptr && WindowCount == 0)
		{
			GLenum res = glewInit();
			assert(res == GLEW_OK);

			if (!(GLEW_VERSION_4_0))
			{
				printf("[WARNING]: OpenGL 4.0+ is not supported on this hardware!\n");
				glfwDestroyWindow(this->window);
				this->window = nullptr;
				return false;
			}

			glEnable(GL_MULTISAMPLE);
			glfwSwapInterval(0);

			glViewport(0, 0, this->width, this->height);
		}
		else
		{
			printf("[ WINDOW ] : Failed to create GLFW Window! \n");
			glfwTerminate();
			return false;
		}



		glfwSetWindowUserPointer(this->window, this);
		glfwSetKeyCallback(this->window, Window::StaticKeyPressCallback);
		glfwSetMouseButtonCallback(this->window, Window::StaticMousePressCallback);
		glfwSetCursorPosCallback(this->window, Window::StaticMouseMoveCallback);
		glfwSetCursorEnterCallback(this->window, Window::StaticMouseEnterLeaveCallback);
		glfwSetScrollCallback(this->window, Window::StaticMouseScrollCallback);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = { (float)width, (float)height };
		io.DeltaTime = 1 / 60.0f;

		ImGui_ImplGlfw_InitForOpenGL(this->window, false);
		ImGui_ImplOpenGL3_Init();

		ImFontConfig config;
		config.OversampleH = 3;
		config.OversampleV = 1;

		ImFont* font = io.Fonts->AddFontFromFileTTF("c:/windows/fonts/tahoma.ttf", 14, &config);

		unsigned char* buffer;
		int width, height, channels;
		io.Fonts->GetTexDataAsRGBA32(&buffer, &width, &height, &channels);

		glfwSetCharCallback(window, ImGui_ImplGlfw_CharCallback);

		InputSystem::InputHandler::CreateHandler();

		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Problem: glewInit failed, something is seriously wrong. */
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}
		fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
		fprintf(stdout, "Status: Using OpenGL %s\n", glGetString(GL_VERSION));
		fprintf(stdout, "Status: GPU Vendor %s\n", glGetString(GL_VENDOR));
		fprintf(stdout, "Status: GPU Render Device %s\n", glGetString(GL_RENDERER));
		
		Window::WindowCount++;

		return this->window != nullptr;
	}

	bool Window::Close()
	{
		if (nullptr != this->window) glfwDestroyWindow(this->window);
		this->window = nullptr;
		Window::WindowCount--;
		if (Window::WindowCount == 0)
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
			glfwTerminate();
		}
		return 0;
	}


	bool Window::ProcessInput(int32 key)
	{
		return (glfwGetKey(this->window, key) == GLFW_PRESS);
	}

	void Window::Update()
	{
		InputSystem::InputHandler::BeginFrame();
		glfwPollEvents();
	}

	void Window::SwapBuffers()
	{
		if (this->window)
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();

			ImGui::NewFrame();
			if (nullptr != this->uiFunc)
				this->uiFunc();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(this->window);
		}
	}

	void Window::Resize()
	{
		if (nullptr != this->window)
		{
			glfwSetWindowSize(this->window, this->width, this->height);

			// setup viewport
			glViewport(0, 0, this->width, this->height);
		}
	}

	void Window::Retitle()
	{
		if (nullptr != this->window) glfwSetWindowTitle(this->window, this->title.c_str());
	}

	void Window::StaticKeyPressCallback(GLFWwindow* win, int32 key, int32 scancode, int32 action, int32 mods)
	{
		Window* window = (Window*)glfwGetWindowUserPointer(win);
		if (ImGui::IsAnyItemHovered())
		{
			ImGui_ImplGlfw_KeyCallback(win, key, scancode, action, mods);
		}
		else if (nullptr != window->keyPressCallback)
			window->keyPressCallback(key, scancode, action, mods);

		InputSystem::InputHandler::HandleKeyEvent(key, scancode, action, mods);
	}

	void Window::StaticMousePressCallback(GLFWwindow* win, int32 button, int32 action, int32 mods)
	{
		Window* window = (Window*)glfwGetWindowUserPointer(win);

		ImGui_ImplGlfw_MouseButtonCallback(win, button, action, mods);

		if (nullptr != window->mousePressCallback)
			window->mousePressCallback(button, action, mods);

		InputSystem::InputHandler::HandleMousePressEvent(button, action, mods);
	}

	void Window::StaticMouseMoveCallback(GLFWwindow* win, float64 x, float64 y)
	{
		Window* window = (Window*)glfwGetWindowUserPointer(win);
		if (nullptr != window->mouseMoveCallback)
			window->mouseMoveCallback(x, y);
		InputSystem::InputHandler::HandleMouseMoveEvent(x, y);
	}

	void Window::StaticMouseEnterLeaveCallback(GLFWwindow* win, int32 mode)
	{
		Window* window = (Window*)glfwGetWindowUserPointer(win);
		if (nullptr != window->mouseLeaveEnterCallback) window->mouseLeaveEnterCallback(mode == 0);
	}

	void Window::StaticMouseScrollCallback(GLFWwindow* win, float64 x, float64 y)
	{
		Window* window = (Window*)glfwGetWindowUserPointer(win);
		if (ImGui::IsAnyItemHovered())
		{
			ImGui_ImplGlfw_ScrollCallback(win, x, y);
		}
		else if (nullptr != window->mouseScrollCallback) window->mouseScrollCallback(x, y);
	}

	void Window::StaticWindowResizeCallback(GLFWwindow* win, int32 x, int32 y)
	{
		Window* window = (Window*)glfwGetWindowUserPointer(win);
		window->width = x;
		window->height = y;
		window->Resize();
		if (nullptr != window->windowResizeCallback)
			window->windowResizeCallback(x, y);
	}

	void Window::StaticCharCallback(GLFWwindow* window, unsigned int key)
	{
		if (ImGui::IsAnyItemHovered())
		{
			ImGui_ImplGlfw_CharCallback(window, key);
		}
	}

	void Window::GetMousePos(float64& x, float64& y)
	{
		glfwGetCursorPos(this->window, &x, &y);
	}
}