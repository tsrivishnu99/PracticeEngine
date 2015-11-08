#include "Renderer.h"


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::draw()
{
	int counter = m_sceneObjects.size();

	for (int i = 0; i < counter; i++)
	{
		//m_sceneObjects[i]->draw(glm::mat4(1.0f));
	}
}