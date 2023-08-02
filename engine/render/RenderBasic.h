#pragma once
 
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

#include <vector>
#include "GL/glew.h"
#include "glm.hpp"

//TODO: Change Triangle to a "Mesh" class.
//TODO: Add functions for Triangle, Cube, and Spheres. With posibilities for debug rendering.

namespace Render
{
	// Vertices are data points in 3D space representing the corners or endpoints of geometric shapes processed by the GPU in OpenGL.
	struct Vertice
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texCoord;
	};

	// PrimitiveType represents the type of primitive (points, lines, or triangles) used in the OpenGL rendering process.
	enum class PrimitiveTypes
	{
		Points,
		Lines,
		Triangles
	};

	// Primitives are basic geometric shapes formed by connecting vertices, which are then rendered and processed by the GPU in OpenGL.
	struct Primitive
	{
		GLuint startIndex;
		GLuint numVertices;
	};

	//IMPLEMENT THIS:
	class Mesh
	{
	public:
		std::vector<Primitive> primitives;

		Mesh(std::vector<Vertice> Vertices, std::vector<GLuint> indices, std::vector<Primitive> primitives);

		void renderMesh(GLuint primitiveIndex);

		void clearBuffers();
		void bindVAO();
		void unBindVAO();

	private:
		GLuint VAO, VBO, EBO;

		void processMesh(std::vector<Vertice> Vertices, std::vector<GLuint> indices);
	};

	Mesh CreateTriangle(float32 width, float32 height);
	Mesh CreatePlane();
	Mesh CreateCube();
	Mesh CreateSphere();
	Mesh CreateCylinder();

	//REPLACE THIS WITH MESH AND CREATE THIS AS A FUNCTION INSTEAD RETURNING A MESH
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