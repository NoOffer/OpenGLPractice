#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>

#include "placeable_obj.h"
#include "mesh.h"

class Model : public PlaceableObj
{
public:
	Model(const char* path);

	inline void SetShader(Shader& shader) { m_Shader = shader; }

	void Draw();

private:
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	//std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	// model data
	std::string directory;
	std::vector<Mesh> meshes;
	Shader m_Shader;
};


