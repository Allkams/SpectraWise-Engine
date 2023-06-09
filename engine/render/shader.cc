#include "config.h"
#include "shader.h"

Shader::Shader(const char* vsPath, const char* fsPath) : vsPath(vsPath), fsPath(fsPath)
{
	LoadShader(vsPath, fsPath);
}

void Shader::LoadShader(const char* vsPath, const char* fsPath)
{
	std::string vsCode;
	std::string fsCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vsPath);
		fShaderFile.open(fsPath);

		std::stringstream vShaderStream, fShaderSteam;

		vShaderStream << vShaderFile.rdbuf();
		fShaderSteam << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vsCode = vShaderStream.str();
		fsCode = fShaderSteam.str();
	}
	catch (std::ifstream::failure e)
	{
		printf("[ Shader ] : ERROR : Shader files did not load.\n");
		assert(false);
	}

	const char* vShaderCode = vsCode.c_str();
	const char* fShaderCode = fsCode.c_str();

	GLuint vsID, fsID;
	int success;
	char info[512];

	vsID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vsID, 1, &vShaderCode, NULL);
	glCompileShader(vsID);

	glGetShaderiv(vsID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vsID, 512, NULL, info);
		printf("[ Shader ] : ERROR : Compilation failure for vertex shader. \n Error log: %s\n", info);
		assert(false);
	}

	fsID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsID, 1, &fShaderCode, NULL);
	glCompileShader(fsID);

	glGetShaderiv(fsID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fsID, 512, NULL, info);
		printf("[ Shader ] : ERROR : Compilation failure for fragment shader. \n Error log: %s\n", info);
		assert(false);
	}

	this->ID = glCreateProgram();
	glAttachShader(ID, vsID);
	glAttachShader(ID, fsID);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, info);
		printf("[ Shader ] : ERROR : Linking failure for shader program. \n Error log: %s\n", info);
		assert(false);
	}
	
	glDeleteShader(vsID);
	glDeleteShader(fsID);
}

void Shader::ReloadShader()
{
	this->Destroy();
	this->LoadShader(this->vsPath.c_str(), this->fsPath.c_str());
}

void Shader::Destroy()
{
	glDeleteProgram(this->ID);
	this->ID = 0xFFFFFFFF;
}

void Shader::Enable()
{
	glUseProgram(this->ID);
}

void Shader::Disable()
{
	glUseProgram(0);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}