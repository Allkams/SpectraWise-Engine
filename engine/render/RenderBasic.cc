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
#include "RenderBasic.h"

namespace Render
{
	Mesh::Mesh(std::vector<Vertice> vertices, std::vector<GLuint> indices, std::vector<Primitive> primitives)
	{
		this->primitives = primitives;

		processMesh(vertices, indices);
	}

	void Mesh::processMesh(std::vector<Vertice> vertices, std::vector<GLuint> indices)
	{
		// Generating Buffers
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		// Binding Buffers
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		// Filling Buffers
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertice), &vertices[0], GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

		// Passing vertice position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)0);

		// Passing vertice color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)offsetof(Vertice, color));

		// Passing vertice texture cords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)offsetof(Vertice, texCoord));

		// unbinding VAO
		glBindVertexArray(0);

	}

	void Mesh::renderMesh(GLuint primitiveIndex)
	{
		if (primitiveIndex <= primitives.size()) {

			//Drawes each primitive
			glDrawElements(GL_TRIANGLES, 1 + primitives[primitiveIndex].numVertices - primitives[primitiveIndex].startIndex, GL_UNSIGNED_INT, (void*)(primitives[primitiveIndex].startIndex * sizeof(GLint)));
		}
	}

	void Mesh::clearBuffers() {
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void Mesh::bindVAO() {
		glBindVertexArray(VAO);
	}

	void Mesh::unBindVAO() {
		glBindVertexArray(0);
	}

	Mesh CreateTriangle(float32 width, float32 height)
	{
		float32 widthPoint = width / 2.0f;
		float32 heightPoint = width / 2.0f;

		Vertice Point1;
		Point1.position = glm::vec3(-widthPoint, -heightPoint, 0.0f);
		Point1.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		Point1.texCoord = glm::vec2(0.0f, 0.0f);

		Vertice Point2;
		Point2.position = glm::vec3(widthPoint, -heightPoint, 0.0f);
		Point2.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		Point2.texCoord = glm::vec2(1.0f, 0.0f);

		Vertice Point3;
		Point3.position = glm::vec3(-0.0f, heightPoint, 0.0f);
		Point3.color = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
		Point3.texCoord = glm::vec2(0.5f, 1.0f);

		Primitive Triangle;
		Triangle.startIndex = 0;
		Triangle.numVertices = 3;

		return Mesh(
			// Vertice Points
			{
				Point1, Point2, Point3
			},
			// Indice order (What Vertice connects to what)
			{
				0, 1, 2
			},
			// Primitives
			{
				Triangle
			}
		);
	}
	
	Mesh CreatePlane(float32 width, float32 height);
	Mesh CreateCube(float32 width, float32 height, float32 depth);
	Mesh CreateSphere(float32 radius);
	Mesh CreateCylinder(float32 radius, float32 height);
}