#include "model.h"

Model::Model(const char* path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(
		path,
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_OptimizeMeshes
	);
}

void Model::Draw()
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw(m_Shader);
}
