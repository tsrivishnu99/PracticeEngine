#pragma once
#include "GLIncludes.h"
#include "Shader.h"

struct Attribute{
	std::string attributeName;
	GLuint size;
	GLenum type;
	GLenum normalize;
	int Offset;
};

class Program
{
private:
	GLuint p_programID;
	int p_numAttributes;
	std::vector<Attribute> p_attributeList;
public:
	Program();
	~Program();

	GLuint getProgramID(){ return p_programID; };
	void attachShaders(Shader A[], int numberOfShaders);
	void attachShader(Shader A);
	void linkProgram();
	void addAttribute(const std::string& attributeName, GLuint size, GLenum type, GLenum normalize, int offset);
	void setAttributePointer();
	void UseProgram();
	void unUseProgram() const;
	Program operator= (Program other);

	GLuint m_MVPLocation;
};

