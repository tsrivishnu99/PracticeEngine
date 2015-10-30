#pragma once
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "GLIncludes.h"
#include "GameObject.h"

class ResourceManager
{
private:
	std::vector<GameObject*> ptr_gameObjects;
	std::vector<Mesh> p_meshes;
	std::vector<Mesh> p_temp_mesh;											//To hold the meshes of a game object temporarily. Used during loading 
	std::vector<Program> p_programs;

	void processNode(aiNode* node, const aiScene* scene, GameObject* gameObject);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Material> loadTextures(aiMaterial* mat, aiTextureType type, TexType enumType);
public:
	ResourceManager();
	~ResourceManager();

	GameObject* loadObject(std::string path, Program program);
};