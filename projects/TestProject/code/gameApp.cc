#include "config.h"
#include "gameApp.h"
#include "vector"
#include "render/RenderBasic.h"
namespace Game
{

	const char* VSProgram = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos, 1.0f);\n"
		"}\0";

	const char* FSProgram = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

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

		unsigned int VShader;
		VShader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(VShader, 1, &VSProgram, NULL);
		glCompileShader(VShader);

		unsigned int FShader;
		FShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(FShader, 1, &FSProgram, NULL);
		glCompileShader(FShader);

		unsigned int ShdProgram;
		ShdProgram = glCreateProgram();

		glAttachShader(ShdProgram, VShader);
		glAttachShader(ShdProgram, FShader);
		glLinkProgram(ShdProgram);

		glUseProgram(ShdProgram);

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

		glDeleteShader(VShader);
		glDeleteShader(FShader);

		return true;
	}

	bool TestApp::Close()
	{
		this->window->Close();
		return true;
	}
}