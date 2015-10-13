#include "Material.h"


Material::Material() :m_textureID(0), m_type(DIFFUSE_MAP)
{
}

Material::Material(aiString FILEPATH) : m_textureID(0), m_type(DIFFUSE_MAP)
{
	m_filePath = FILEPATH;
}


Material::~Material()
{
	glDeleteSamplers(1, &m_textureID);
}


bool Material::loadTexture(aiString FILEPATH)
{
	m_filePath = FILEPATH;

	return loadTexture();
}

bool Material::loadTexture()
{
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	int width, height;

	unsigned char* image = SOIL_load_image(m_filePath.C_Str(), &width, &height, 0, SOIL_LOAD_RGBA);


	// Using this image, we can call glTexImage2D to create a 2D texture. Parameters: target GL_TEXTURE_2D, level of detail (0 is base, x is xth mipmap reduction), internal format, 
	// width, height, border (if we're drawing a border around the image), format of texel data (must match internal format), type of texel data, and a pointer to image data in memory.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);

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