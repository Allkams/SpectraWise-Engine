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
#include <vector>
#include <chrono>
#include "render/RenderBasic.h"
#include "render/shader.h"
#include "render/camera.h"
#include "render/input/inputManager.h"


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
		int32 w;
		int32 h;
		window->GetSize(w, h);
		RenderUtils::Camera Cam(glm::vec3(0));

		Shader shader = Shader("./shaders/VertexShader.vs", "./shaders/FragementShader.fs");

		shader.Enable();

		InputSystem::Keyboard* kbd = InputSystem::GetDefaultKeyboard();
		InputSystem::Mouse* mouse = InputSystem::GetDefaultMouse();

		Cam.setProjection(w, h, 0.01f, 1000.0f);
		Cam.setViewMatrix();

		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 view = Cam.GetProjection() * Cam.GetViewMatrix() * trans;

		shader.setMat4("transform", view);

		Render::Mesh triangle = Render::CreateTriangle(1.0f, 1.0f);
		Render::Mesh Cube = Render::CreateCube(1.0f, 1.0f, 1.0f);

		glEnable(GL_DEPTH_TEST);

		//Cam.FOV = 120.0f;

		Cam.Position = { 0, 0, 10 };
		Cam.Target = { 0,0,0 };
		Cam.setViewMatrix(true);
		Cam.shouldTarget = false;
		Cam.setViewProjection();
		float dt = 0.016667f;
		while (this->window->IsOpen())
		{
			auto timeStart = std::chrono::steady_clock::now();
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

			// Accept fragment if it closer to the camera than the former one
			glDepthFunc(GL_LESS);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (kbd->held[InputSystem::Key::Code::F1])
			{
				shader.ReloadShader();
			}

			if (kbd->held[InputSystem::Key::Code::Escape])
			{
				this->window->Close();
				break;
			}

			if (kbd->held[InputSystem::Key::Code::W])
			{
				Cam.Move(RenderUtils::FORWARD, dt);
			}
			if (kbd->held[InputSystem::Key::Code::S])
			{
				Cam.Move(RenderUtils::BACKWARD, dt);
			}
			if (kbd->held[InputSystem::Key::Code::A])
			{
				Cam.Move(RenderUtils::LEFT, dt);
			}
			if (kbd->held[InputSystem::Key::Code::D])
			{
				Cam.Move(RenderUtils::RIGHT, dt);
			}

			if (kbd->held[InputSystem::Key::Code::LeftControl])
			{
				Cam.Look(mouse->delta.x, -mouse->delta.y);
			}
			Cam.setViewMatrix(false);
			view = Cam.GetProjection() * Cam.GetViewMatrix() * trans;

			shader.setMat4("transform", view);
			Cube.bindVAO();
			Cube.renderMesh(0);
			Cube.unBindVAO();
			this->window->Update();
			this->window->SwapBuffers();

			auto timeEnd = std::chrono::steady_clock::now();
			dt = std::chrono::duration<double>(timeEnd - timeStart).count();
		}

		return true;
	}

	bool TestApp::Close()
	{
		this->window->Close();
		return true;
	}
}