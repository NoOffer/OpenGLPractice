#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "texture.h"
#include "shader.h"
#include "index_buffer.h"
#include "vertex_array.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};


class Mesh
{
public:
	// mesh data
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices/*, std::vector<Texture> textures*/);

	void Bind();
	void Unbind();

	void Draw(Shader& shader);

private:
	// render data
	IndexBuffer m_IB;
	VertexArray m_VA;
	//std::vector<Texture> textures;
};

