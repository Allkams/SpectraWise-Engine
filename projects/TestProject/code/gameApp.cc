#include "config.h"
#include "gameApp.h"

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

		while (this->window->IsOpen())
		{

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			if (this->window->ProcessInput(GLFW_KEY_ESCAPE))
			{
				this->window->Close();
				break;
			}

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