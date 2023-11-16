// 
// Copyright 2023 Alexander Marklund (Allkams02@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated
// documentation files(the �Software�), to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the following conditions :
//
// The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED �AS IS�, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
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
#include "render/camera.h"


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
		RenderUtils::Camera Cam; //Not fully implemented yet!

		Shader shader = Shader("./shaders/VertexShader.vs", "./shaders/FragementShader.fs");

		shader.Enable();

		glm::mat4 perspect = Cam.GetPerspective(800, 600, 0.0f, 1000.0f);

		glm::mat4 trans = glm::mat4(1.0f);

		glm::mat4 view = perspect * Cam.GetViewMatrix() * trans;

		shader.setMat4("transform", view);

		Render::Mesh triangle = Render::CreateTriangle(1.0f, 1.0f);
		Render::Mesh Cube = Render::CreateCube(1.0f, 1.0f, 1.0f);

		//Cam.FOV = 120.0f;

		while (this->window->IsOpen())
		{

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glEnable(GL_DEPTH_TEST);

			// Accept fragment if it closer to the camera than the former one
			glDepthFunc(GL_LESS);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (this->window->ProcessInput(GLFW_KEY_F1))
			{
				shader.ReloadShader();
			}

			if (this->window->ProcessInput(GLFW_KEY_ESCAPE))
			{
				this->window->Close();
				break;
			}

			if (this->window->ProcessInput(GLFW_KEY_W))
			{
				Cam.Move(RenderUtils::FORWARD, 0.016667f);
				view = perspect * Cam.GetViewMatrix() * trans;
			}
			else if (this->window->ProcessInput(GLFW_KEY_S))
			{
				Cam.Move(RenderUtils::BACKWARD, 0.016667f);
				view = perspect * Cam.GetViewMatrix() * trans;
			}
			else if (this->window->ProcessInput(GLFW_KEY_A))
			{
				Cam.Move(RenderUtils::LEFT, 0.016667f);
				view = perspect * Cam.GetViewMatrix() * trans;
			}
			else if (this->window->ProcessInput(GLFW_KEY_D))
			{
				Cam.Move(RenderUtils::RIGHT, 0.016667f);
				view = perspect * Cam.GetViewMatrix() * trans;
			}

			Cube.bindVAO();
			Cube.renderMesh(0);
			Cube.unBindVAO();

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