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