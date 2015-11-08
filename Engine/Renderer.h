#pragma once
#include "GLIncludes.h"
#include "GameObject.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	std::vector<GameObject*> m_sceneObjects;

	void draw();
};

