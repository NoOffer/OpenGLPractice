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
	Model(const char* path, Shader* shaderRef);
	Model(Model&& other) noexcept;
	
	inline void SetShaderRef(Shader* shaderRef) { m_ShaderRef = shaderRef; }
	inline Shader* GetShaderRef() { return m_ShaderRef; }

	void Render();

private:
	void ParseNode(aiNode* node, const aiScene* scene);
	//std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	// model data
	std::vector<Mesh> m_Meshes;
	Shader* m_ShaderRef;
};


