#include "Program.h"


Program::Program() : p_numAttributes(0)
{
	p_programID = glCreateProgram();
}


Program::~Program()
{
	glDeleteProgram(p_programID);
}

void Program::attachShaders(Shader A[], int numberOfShaders)
{
	for (int i = 0; i < numberOfShaders; i++)
	{
		glAttachShader(p_programID, A[i].getShaderID());
	}
}

void Program::attachShader(Shader A)
{
	glAttachShader(p_programID, A.getShaderID());
}

void Program::addAttribute(const std::string& attributeName, GLuint size, GLenum type, GLenum normalize, int offset)
{
	Attribute att;
	att.attributeName = attributeName;
	att.size = size;
	att.type = type;
	att.normalize = normalize;
	att.Offset = offset;
	p_attributeList.push_back(att);

	p_numAttributes++;
}

void Program::linkProgram()
{
	glLinkProgram(p_programID);
}

void Program::UseProgram() const
{
	glUseProgram(p_programID);
	for (int i = 0; i < p_numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void Program::unUseProgram() const
{
	glUseProgram(0);
	for (int i = 0; i < p_numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void Program::setAttributePointer()
{
	for (int i = 0; i < p_numAttributes; i++)
	{
		glVertexAttribPointer(glGetAttribLocation(p_programID, p_attributeList[i].attributeName.c_str()), 
							p_attributeList[i].size,
							p_attributeList[i].type,
							p_attributeList[i].normalize,
							sizeof(Vertex),
							(void*)p_attributeList[i].Offset);
	}
}