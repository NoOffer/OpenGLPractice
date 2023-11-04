#include "model.h"

Model::Model(const char* path, Shader* shaderRef) : m_ShaderRef(shaderRef)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(
		path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_OptimizeMeshes
	);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "[Assimp Error] " << importer.GetErrorString() << std::endl;
		return;
	}

	ParseNode(scene->mRootNode, scene);
}

void Model::ParseNode(aiNode* node, const aiScene* scene)
{
	// process all the node¡¯s meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		Vertex vertex;
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			// process vertex positions, normals and texture coordinates
			vertex.position = vec3(mesh->mVertices[i].x / 2, mesh->mVertices[i].y / 2, mesh->mVertices[i].z / 2);
			vertex.normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			if (mesh->mTextureCoords[0])  // If the mesh contain texture coordinates
			{
				vertex.texCoords = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			}

			vertices.push_back(vertex);
		}

		// process indices
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		// process material
		//if (mesh->mMaterialIndex >= 0)
		//{

		//}

		m_Meshes.push_back(*(new Mesh(vertices, indices)));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ParseNode(node->mChildren[i], scene);
	}

}

void Model::Draw()
{
	for (unsigned int i = 0; i < m_Meshes.size(); i++) { m_Meshes[i].Draw(m_ShaderRef); }
}
