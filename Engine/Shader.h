#pragma once
#include "GLIncludes.h"

class Shader
{
private:
	GLuint p_shaderID;

	std::string p_readShader(std::string fileName);
	GLuint p_createShader(std::string sourceCode, GLenum shaderType);

public:
	Shader(std::string fileName, GLenum shaderType);
	Shader();
	~Shader();

	void init(std::string fileName, GLenum shaderType);
	
	GLuint getShaderID() const;

};

