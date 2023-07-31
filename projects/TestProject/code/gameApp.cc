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
#include "gameApp.h"
#include "vector"
#include "render/RenderBasic.h"
#include "render/shader.h"


namespace Game
{

	TestApp::TestApp()
	{
		//Empty
	}

	TestApp::~TestApp()
	{
		//Empty
	}

	bool TestApp::Open()
	{

		this->window = new DISPLAY::Window;
		if (window->Open())
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);



			return true;
		}

		return false;
	}

	bool TestApp::Run()
	{
		//PreWork

		Shader shader = Shader("./shaders/VertexShader.vs", "./shaders/FragementShader.fs");

		shader.Enable();

		Render::Triangle triangle;

		std::vector<float> tri = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		triangle.MakeTriangle(tri);

		while (this->window->IsOpen())
		{

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			if (this->window->ProcessInput(GLFW_KEY_ESCAPE))
			{
				this->window->Close();
				break;
			}

			triangle.DrawTriangle();

			this->window->Update();
		}

		return true;
	}

	bool TestApp::Close()
	{
		this->window->Close();
		return true;
	}
}