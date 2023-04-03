#include "mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices/*, std::vector<Texture> textures*/)
	: m_IB(IndexBuffer(&(indices[0]), indices.size()))
{
	m_VA.Bind();
	// Vertices
	VertexBuffer vb(&(vertices[0]), sizeof(float) * vertices.size());  // Create vertext buffer
	VertexBufferLayout layout;										   // Create buffer layout
	// Setup layout
	layout.Push<float>(3);  // Vertex position
	layout.Push<float>(3);  // Vertex normal
	layout.Push<float>(2);  // Vertex texcoord
	// Bind vb and layout to va
	m_VA.SetupArray(vb, layout);
}

void Mesh::Bind()
{
	m_VA.Bind();
	m_IB.Bind();
}

void Mesh::Unbind()
{
	m_VA.Unbind();
	m_IB.Unbind();
}

void Mesh::Draw(Shader& shader)
{
	// draw mesh
	Bind();
	shader.Bind();
	glDrawElements(GL_TRIANGLES, m_IB.GetCount(), GL_UNSIGNED_INT, 0);
}
