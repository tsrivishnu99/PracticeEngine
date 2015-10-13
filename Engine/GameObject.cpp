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

void GameObject::draw()
{
	p_program.UseProgram();
	/*
		Entire draw call need to addressed here
	*/
	for (GLuint i = 0; i < p_mesh.size(); i++)
		p_mesh[i].draw();
}

