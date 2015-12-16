#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::processNode(aiNode* node, const aiScene* scene, GameObject* gameObject)
{
	//Process all of the nodes meshes
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		gameObject->setMesh(processMesh(mesh, scene));
	}

	if (node->mNumChildren > 0)
	{
		
		// Then do the same for each of the child
		for (GLuint i = 0; i < node->mNumChildren; i++)
		{
			//Create the child game object
			GameObject* child = new GameObject;//(GameObject*)_mm_malloc(sizeof(GameObject), 16);
			child->setProgram(p_programs.back());
			//Initialize the mesh of the child object
			processNode(node->mChildren[i], scene, child);
			//Push the child object onto the global database
			ptr_gameObjects.push_back(child);
			//Set the parent of the child as the current object
			child->m_parent = gameObject;
			gameObject->m_child.push_back(child);
		}
	}
}

Mesh ResourceManager::processMesh(aiMesh* mesh, const aiScene* scene)
{
	Mesh* gameMesh = new Mesh;

	//std::vector<Vertex> vertices;
	//std::vector<GLuint> indices;
	//std::vector<Material> textures;

	//if (mesh->mTextureCoords[0])
	//{
	//	if (mesh->mTangents != nullptr)
	//	{
	//		for (GLuint i = 0; i < mesh->mNumVertices; i++)
	//		{
	//			Vertex vertex;
	//			vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
	//			vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
	//			vertex.tangent = glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
	//			vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

	//			vertices.push_back(vertex);
	//		}
	//	}
	//	else
	//	{
	//		for (GLuint i = 0; i < mesh->mNumVertices; i++)
	//		{
	//			Vertex vertex;
	//			vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
	//			vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
	//			vertex.tangent = glm::vec3(0.0f);
	//			vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

	//			vertices.push_back(vertex);
	//		}
	//	}
	//}
	//else
	//{
	//	if (mesh->mTangents != nullptr)
	//	{
	//		for (GLuint i = 0; i < mesh->mNumVertices; i++)
	//		{
	//			Vertex vertex;
	//			vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
	//			vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
	//			vertex.tangent = glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
	//			vertex.texCoord = glm::vec2(0.0f);

	//			vertices.push_back(vertex);
	//		}
	//	}
	//	else
	//	{
	//		for (GLuint i = 0; i < mesh->mNumVertices; i++)
	//		{
	//			Vertex vertex;
	//			vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
	//			vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
	//			vertex.tangent = glm::vec3(0.0f);
	//			vertex.texCoord = glm::vec2(0.0f);

	//			vertices.push_back(vertex);
	//		}
	//	}
	//}

	//for (GLuint i = 0; i < mesh->mNumFaces; i++)
	//{
	//	aiFace face = mesh->mFaces[i];
	//	for (GLuint j = 0; j < face.mNumIndices; j++)
	//		indices.push_back(face.mIndices[j]);
	//}
	//
	//gameMesh->init(vertices, indices, &p_programs.back());

	////Process Material
	//if (mesh->mMaterialIndex >= 0)
	//{
	//	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	//	std::vector<Material> diffuseMaps = loadTextures(material, aiTextureType_DIFFUSE, DIFFUSE_MAP);
	//	gameMesh->m_material = diffuseMaps;
	//	std::vector<Material> specularMaps = loadTextures(material, aiTextureType_SPECULAR, SPECULAR_MAP);
	//	gameMesh->addMaterials(specularMaps);
	//	std::vector<Material> NormalMaps = loadTextures(material, aiTextureType_NORMALS, NORMAL_MAP);
	//	gameMesh->addMaterials(NormalMaps);

	//}

	return (*gameMesh);
}

std::vector<Material> ResourceManager::loadTextures(aiMaterial* mat, aiTextureType type, TexType enumType)
{

	std::vector<Material> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		Material tex;
		tex.m_type = enumType;
		tex.loadTexture(str);

		textures.push_back(tex);
	}
	
	return textures;
}

GameObject* ResourceManager::loadObject(std::string path, Program program)
{
	p_temp_mesh.clear();
	p_programs.push_back(program);

	GameObject* object = new GameObject;//(GameObject*) _mm_malloc(sizeof(GameObject),16);
	
	//Debug shit
	//=====================================================================================

	Mesh *mesh = new Mesh();

	std::vector<Vertex> vertices;
	Vertex a;
	a.position = glm::vec3(0.95f, 0.0f, -0.5f);
	a.normal = glm::vec3(0.0f,0.25f,0.0f);
	//a.tangent = glm::vec3(0.4);
	//a.texCoord = glm::vec2(0.2);

	vertices.push_back(a);
	a.position = glm::vec3(-0.5f, 0.7f, -0.5f);
	a.normal = glm::vec3(1.0f,0.0f,0.0f);
	vertices.push_back(a);
	a.position = glm::vec3(-0.35f, -0.5f, -0.5f);
	vertices.push_back(a);

	std::vector<GLuint> indices = { 0, 1, 2 };

	mesh->init(vertices, indices, &program);

	object->setMesh(*mesh);
	//=====================================================================================


	/*Assimp::Importer import;

	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return nullptr;
	}
	*/

	object->setProgram(program);
	//processNode(scene->mRootNode, scene, object);

	ptr_gameObjects.push_back(object);
	return (object);
}