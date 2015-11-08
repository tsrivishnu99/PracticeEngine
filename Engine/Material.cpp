#include "Material.h"


Material::Material() :m_textureID(0), m_type(DIFFUSE_MAP)
{
}

Material::Material(aiString FILEPATH) : m_textureID(0), m_type(DIFFUSE_MAP)
{
	addTexture(FILEPATH);
}


Material::~Material()
{
	glDeleteSamplers(1, &m_textureID);
}

void Material::addTexture(aiString FILEPATH)
{
	int width, height;

	unsigned char* image = SOIL_load_image(FILEPATH.C_Str(), &width, &height, 0, SOIL_LOAD_RGBA);

	p_images.push_back(image);
	p_width.push_back(width);
	p_height.push_back(height);
}

bool Material::loadTexture(aiString FILEPATH)
{
	addTexture(FILEPATH);

	return loadTexture();
}

bool Material::loadTexture()
{
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureID);

	int count = p_images.size();

	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, p_width[0], p_height[0], count,GL_CLAMP, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, NULL);

	for (int i = 0; i < count; i++)
	{
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, i, 0, 0, 0, p_width[i], p_height[i], 1, GL_RGBA, GL_UNSIGNED_BYTE, p_images[i]);
	}

	// Sets texture parameters, given a target, symbolic name of the texture parameter, and a value for that parameter.
	// Valid symbolic names are GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_TEXTURE_WRAP_S, or GL_TEXTURE_WRAP_T.
	// Each has their own different set of values as well.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// Generates a mipmap for the texture, and there's no reason not to.
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}