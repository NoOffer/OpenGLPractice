#include "Model.h"

#include "glm/gtc/matrix_transform.hpp"

Model::Model()
{
	// Vertices
	float vertPos[24] = {
		// Position   UV Coord
		-1.0f, -1.0f,  0.0f,  // 0
		 1.0f, -1.0f,  1.0f,  // 1
		 1.0f,  1.0f,  1.0f,  // 2
		-1.0f,  1.0f,  0.0f,  // 3
		-1.0f, -1.0f, -0.0f,  // 4
		 1.0f, -1.0f, -1.0f,  // 5
		 1.0f,  1.0f, -1.0f,  // 6
		-1.0f,  1.0f, -0.0f,  // 7
	};
	VertexBuffer vb(vertPos, sizeof(float) * 24);	  // Create vertext buffer
	VertexBufferLayout layout;						  // Create buffer layout
	// Setup layout
	layout.Push<float>(3);
	// Bind vb and layout to va
	m_VA.SetupArray(vb, layout);

	// Indices
	unsigned int vertIdx[36] = {
		0, 1, 2, 0, 2, 3,
		1, 5, 6, 1, 6, 2,
		5, 4, 7, 5, 7, 6,
		4, 0, 3, 4, 3, 7,
		3, 2, 6, 3, 6, 7,
		0, 4, 5, 0, 5, 1
	};
	m_IB.SetData(vertIdx, 36);

	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Model::~Model() {}

void Model::Translate(float xOffset, float yOffset, float zOffset)
{
	m_Position += glm::vec3(xOffset, yOffset, zOffset);
}

void Model::Rotate(float xOffset, float yOffset, float zOffset)
{
	m_Rotation += glm::vec3(xOffset, yOffset, zOffset);
}

void Model::Scale(float xScale, float yScale, float zScale)
{
	m_Scale *= glm::vec3(xScale, yScale, zScale);
}

glm::mat4  Model::GetModelMatrix()
{
	return glm::scale(glm::translate(glm::mat4(1.0f), m_Position), m_Scale);
}

void Model::Bind()
{
	m_VA.Bind();
	m_IB.Bind();
	m_Shader.Bind();
}

void Model::Unbind()
{
	m_VA.Unbind();
	m_IB.Unbind();
	m_Shader.Unbind();
}

void Model::Draw()
{
	Bind();
	//m_Shader.Unbind();
	// Drawcall
	glDrawElements(GL_TRIANGLES, m_IB.GetCount(), m_IB.GetIndexType(), nullptr);
}