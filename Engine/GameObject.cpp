#include "GameObject.h"

#pragma region constructor and destructor
GameObject::GameObject()
{
}

GameObject::GameObject( const GameObject &copy)
{
	m_transform = copy.m_transform;
	p_program = copy.p_program;
	p_mesh = copy.p_mesh;
}

GameObject::~GameObject()
{
}
#pragma endregion constructor and destructor

void GameObject::setProgram(Program program)
{
	p_program = program;
}

void GameObject::setMesh(Mesh m)
{
	p_mesh.push_back(m);
}

void GameObject::draw()// glm::mat4 &Transformation)
{
	p_program.UseProgram();
	/*
		Entire draw call need to addressed here
	*/

	glm::mat4 M = m_transform.getTransformationMatrix();
	//glm::mat4 model = glm::translate(glm::vec3(0.0f, 0.0f, -10.0f));//M * Transformation;
	//glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//glm::mat4 proj = glm::perspective(45.0f, 800.0f / 800.0f, 0.1f, 100.0f);

	//M = proj * view * model;

	glUniformMatrix4fv(p_program.m_MVPLocation, 1, GL_FALSE, glm::value_ptr(M));

	for (GLuint i = 0; i < p_mesh.size(); i++)
		p_mesh[i].draw();

	for (GLuint i = 0; i < m_child.size(); i++)
	{
		m_child[i]->draw();
	}
}

