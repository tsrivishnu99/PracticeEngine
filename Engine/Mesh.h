#pragma once
#include "GLIncludes.h"
#include "Program.h"
#include "Material.h"

class Mesh
{
private:
	int p_totalNumberOfVertices;
	GLuint p_VertexBufferId;
	GLuint p_IndexBufferId;

public:
	Mesh();
	~Mesh();
	Mesh(const Mesh &copy);

	void init(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, Program* program);
	void draw(Program *program);
	void addMaterials(std::vector<Material> textures);

	std::vector<Material> m_material;
	GLenum m_primitiveType;												// This defines the type of primitive the mesh is made of eg: triangles or quads or patches
	GLuint m_VertexArrayObjectID;											// This is will be used during the render call to bing the ELEMENT ARRAY
};


