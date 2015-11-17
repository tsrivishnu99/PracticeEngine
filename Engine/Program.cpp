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
	att.loc = glGetAttribLocation(p_programID, attributeName.c_str());

	p_attributeList.push_back(att);

	p_numAttributes++;
}

void Program::linkProgram()
{
	glLinkProgram(p_programID);
}

void Program::UseProgram()
{
	glUseProgram(p_programID);
	setAttributePointer();
	for (int i = 0; i < p_numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}

	GLuint i = glGetUniformLocation(p_programID, "MVP");
	//m_MVPLocation = glGetUniformLocation(p_programID, "MVP");

	if (i != (unsigned int) (-1))
		m_MVPLocation = i;
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
	//GLuint loc;
	for (int i = 0; i < p_numAttributes; i++)
	{
		glVertexAttribPointer(p_attributeList[i].loc, 
							p_attributeList[i].size,
							p_attributeList[i].type,
							p_attributeList[i].normalize,
							sizeof(Vertex),
							(void*)p_attributeList[i].Offset);
	}
}

Program Program::operator= (Program other)
{
	p_programID = other.p_programID;
	p_numAttributes = other.p_numAttributes;
	p_attributeList = other.p_attributeList;

	return *this;
}