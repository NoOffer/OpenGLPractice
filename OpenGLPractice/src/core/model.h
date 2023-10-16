#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "basic.h"

#include "placeable_obj.h"
#include "mesh.h"

class Model : public PlaceableObj
{
public:
	Model(const char* path, Shader& shader);

	inline void SetShader(Shader& shader) { m_Shader = shader; }

	void Draw();

private:
	void ParseNode(aiNode* node, const aiScene* scene);
	//std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	// model data
	std::vector<Mesh> m_Meshes;
	Shader m_Shader;
};


