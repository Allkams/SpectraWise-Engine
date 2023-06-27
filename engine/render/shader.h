#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <glm.hpp>

//Note: Maybe change to Create Shader instead of constructor.

class Shader 
{
public:
	std::string vsPath = "";
	std::string fsPath = "";
	GLuint ID;

	Shader(const char* vsPath, const char* fsPath);
	
	void Destroy();

	void ReloadShader();

	void Enable();
	void Disable();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

	void setVec2(const std::string& name, glm::vec2 value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
	void setVec4(const std::string& name, glm::vec4 value) const;

	void setMat4(const std::string& name, glm::mat4 value) const;
private:
	void LoadShader(const char* vsPath, const char* fsPath);

};