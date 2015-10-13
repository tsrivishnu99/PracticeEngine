#pragma once
#include "GLIncludes.h"
#include "assimp\texture.h"

enum TexType {DIFFUSE_MAP, SPECULAR_MAP, NORMAL_MAP};

class Material
{
public:
	Material();
	~Material();
	Material(aiString FILEPATH);

	bool loadTexture(aiString FILEPATH);
	bool loadTexture();

	GLuint m_textureID;
	TexType m_type;
	aiString m_filePath;
};

