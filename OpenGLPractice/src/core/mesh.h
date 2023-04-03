#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "texture.h"
#include "shader.h"
#include "index_buffer.h"
#include "vertex_array.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};


class Mesh
{
public:
	// mesh data
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	void Bind();
	void Unbind();

	void Draw(Shader& shader);

private:
	// render data
	VertexBuffer m_VB;
	IndexBuffer m_IB;
	VertexArray m_VA;
	std::vector<Texture> textures;

	void SetupMesh();
};


