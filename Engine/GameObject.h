#pragma once
#include "GLIncludes.h"
#include "Material.h"
#include "Mesh.h"
#include "Program.h"
#include "Transform.h"

class GameObject
{
private:
	std::vector<Mesh> p_mesh;
	Program p_program;
	
public:
	GameObject();
	GameObject(const GameObject &copy);
	~GameObject();
	
	void setProgram(Program program);
	void setMesh(Mesh m);
	void draw();													// Draw call

	GameObject* m_parent;
	std::vector<GameObject*> m_child;
	Transform m_transform;
} __declspec(align(16));

