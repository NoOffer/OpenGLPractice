#include "Model.h"

#include "glm/gtc/matrix_transform.hpp"

Model::Model()
{
	// Vertices
	float vertPos[16] = {
		// Position   UV Coord
		-1.0f, -1.0f, 0.0f, 0.0f,  // 0
		 1.0f, -1.0f, 1.0f, 0.0f,  // 1
		 1.0f,  1.0f, 1.0f, 1.0f,  // 2
		-1.0f,  1.0f, 0.0f, 1.0f,  // 3
	};
	VertexBuffer vb(vertPos, sizeof(float) * 16);	  // Create vertext buffer
	VertexBufferLayout layout;						  // Create buffer layout
	// Setup layout
	layout.Push<float>(2);
	layout.Push<float>(2);
	// Bind vb and layout to va
	m_VA.SetupArray(vb, layout);

	// Indices
	unsigned int vertIdx[6] = {
		0, 1, 2,
		0, 2, 3
	};
	Model::m_IB = IndexBuffer(vertIdx, 6);			  // Create index buffer

	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Model::~Model() {}

void Model::Translate(glm::vec3 v)
{
	m_Position += v;
}

void Model::Rotate(glm::vec3 v)
{
	m_Rotation += v;
	m_Rotation %= 360.0f;
}

void Model::Scale(glm::vec3 v)
{
	m_Scale += v;
}

glm::mat4  Model::GetModelMatrix()
{
	return glm::scale(glm::translate(glm::mat4(1.0f), m_Position), m_Scale);
}

void Model::Bind()
{
	m_VA.Bind();
	m_IB.Bind();
}

void Model::Unbind()
{
	m_VA.Unbind();
	m_IB.Unbind();
}