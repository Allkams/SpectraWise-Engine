#pragma once

#include "GL/glew.h"
#include <vector>

namespace Render
{
	/*struct Vertices
	{
		Vec3 Pos
		Vec4 Color
		...
	};*/

	class Triangle
	{
	public:
		Triangle();
		~Triangle();

		void MakeTriangle(std::vector<float> vertices);

		void DrawTriangle();

	private:
		GLuint VBO;
		GLuint EBO;
		GLuint VAO;
	};
}