#pragma once

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

#include <functional>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

/*
* TODOS:
*	- Add SetSize
*	- Add GetSize
*	- Add a Title variable
*	- Add Setter and Getter for title.
*	- More inputs.
*/

namespace DISPLAY
{
	class Window
	{
	public:
		Window();
		~Window();

		void SetSize(int32 width, int32 height);
		void GetSize(int32& width, int32& height);
		void SetTitle(const std::string& title);

		bool Open();
		bool Close();
		const bool IsOpen() const;

		void Update();
		void SwapBuffers();

		void SetKeyPressFunction(const std::function<void(int32, int32, int32, int32)>& func);
		void SetMousePressFunction(const std::function<void(int32, int32, int32)>& func);
		void SetMouseMoveFunction(const std::function<void(double, double)>& func);
		void SetMouseEnterLeaveFunction(const std::function<void(bool)>& func);
		void SetMouseScrollFunction(const std::function<void(double, double)>& func);
		void SetWindowResizeFunction(const std::function<void(int32, int32)>& func);

		void SetUiRender(const std::function<void()>& func);

		void GetMousePos(float64& x, float64& y);

		bool ProcessInput(int32 key);

	private:
		static void StaticKeyPressCallback(GLFWwindow* win, int32 key, int32 scancode, int32 action, int32 mods);
		static void StaticMousePressCallback(GLFWwindow* win, int32 button, int32 action, int32 mods);
		static void StaticMouseMoveCallback(GLFWwindow* win, float64 x, float64 y);
		static void StaticMouseEnterLeaveCallback(GLFWwindow* win, int32 mode);
		static void StaticMouseScrollCallback(GLFWwindow* win, float64 x, float64 y);
		static void StaticWindowResizeCallback(GLFWwindow* win, int32  x, int32  y);

		static void StaticCharCallback(GLFWwindow* window, unsigned int key);

		void Resize();
		void Retitle();

		static int32 WindowCount;

		std::function<void(int32, int32, int32, int32)> keyPressCallback;
		std::function<void(int32, int32, int32)> mousePressCallback;
		std::function<void(double, double)> mouseMoveCallback;
		std::function<void(bool)> mouseLeaveEnterCallback;
		std::function<void(double, double)> mouseScrollCallback;
		std::function<void(int32, int32)> windowResizeCallback;
		std::function<void()> uiFunc;

		int32 width;
		int32 height;
		std::string title;
		GLFWwindow* window;
	};

	inline void Window::SetSize(int32 width, int32 height)
	{
		this->width = width;
		this->height = height;
		if (nullptr != this->window) this->Resize();
	}

	inline void Window::GetSize(int32& width, int32& height)
	{
		width = this->width;
		height = this->height;

	}

	inline void Window::SetTitle(const std::string& title)
	{
		this->title = title;
		if (nullptr != this->window) this->Retitle();
	}

	inline const bool Window::IsOpen() const
	{
		return nullptr != this->window;
	}

	inline void Window::SetKeyPressFunction(const std::function<void(int32, int32, int32, int32)>& func)
	{
		this->keyPressCallback = func;
	}

	inline void Window::SetMousePressFunction(const std::function<void(int32, int32, int32)>& func)
	{
		this->mousePressCallback = func;
	}

	inline void Window::SetMouseMoveFunction(const std::function<void(double, double)>& func)
	{
		this->mouseMoveCallback = func;
	}

	inline void Window::SetMouseEnterLeaveFunction(const std::function<void(bool)>& func)
	{
		this->mouseLeaveEnterCallback = func;
	}

	inline void Window::SetMouseScrollFunction(const std::function<void(double, double)>& func)
	{
		this->mouseScrollCallback = func;
	}

	inline void Window::SetWindowResizeFunction(const std::function<void(int32, int32)>& func)
	{
		this->windowResizeCallback = func;
	}


	inline void Window::SetUiRender(const std::function<void()>& func)
	{
		this->uiFunc = func;
	}
}