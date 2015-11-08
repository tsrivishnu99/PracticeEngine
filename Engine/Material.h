#pragma once
#include "GLIncludes.h"
#include "assimp\texture.h"

enum TexType {DIFFUSE_MAP, SPECULAR_MAP, NORMAL_MAP};

class Material
{
private:
	std::vector<unsigned char*> p_images;
	std::vector<int> p_width;
	std::vector<int> p_height;

public:
	Material();
	~Material();
	Material(aiString FILEPATH);

	bool loadTexture(aiString FILEPATH);
	bool loadTexture();
	void addTexture(aiString FILEPATH);

	GLuint m_textureID;
	TexType m_type;
};

