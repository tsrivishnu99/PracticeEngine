#include "Mesh.h"


Mesh::Mesh() :p_totalNumberOfVertices(0), m_VertexArrayObjectID(0), p_VertexBufferId(0), p_IndexBufferId(0), m_primitiveType(GL_TRIANGLES)
{
}

Mesh::~Mesh()
{
}

Mesh::Mesh(const Mesh &copy)
{
	p_totalNumberOfVertices = copy.p_totalNumberOfVertices;
	p_VertexBufferId = copy.p_VertexBufferId;
	p_IndexBufferId = copy.p_IndexBufferId;
	m_primitiveType = copy.m_primitiveType;
	m_VertexArrayObjectID = copy.m_VertexArrayObjectID;
	m_material = copy.m_material;
}

void Mesh::addMaterials(std::vector<Material> textures)
{
	std::vector<Material>::iterator it;
	for (it = textures.begin(); it != textures.end(); it++)
	{
		m_material.push_back(*it);
	}
}

void Mesh::init(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, Program *program)
{
	p_totalNumberOfVertices = indices.size();

	glGenVertexArrays(1, &m_VertexArrayObjectID);
	glBindVertexArray(m_VertexArrayObjectID);

	glGenBuffers(1, &p_VertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, p_VertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &p_IndexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_IndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	/*glBindVertexArray(m_VertexArrayObjectID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_IndexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, p_VertexBufferId);
	*/
	program->setAttributePointer();

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//Send the data to GPU and set up the VAO
}

void Mesh::draw()
{
	glBindVertexArray(m_VertexArrayObjectID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_IndexBufferId);
	glDrawElements(GL_TRIANGLES, p_totalNumberOfVertices, GL_UNSIGNED_BYTE, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
