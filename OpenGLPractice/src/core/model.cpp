#include "model.h"

#include "glm/gtc/matrix_transform.hpp"

Model::Model()
{
	// Vertices
	float vertPos[288] = {
		// Position           Normal              Texcoord
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,  // 0
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,  // 3
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,  // 2
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,  // 2
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,  // 1
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,  // 0

		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,  // 6
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,  // 7
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,  // 4
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,  // 4
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,  // 5
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,  // 6

		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,  // 0
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,  // 4
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,  // 7
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,  // 7
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  // 3
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,  // 0

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  // 6
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,  // 5
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,  // 1
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,  // 1
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,  // 2
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  // 6

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,  // 0
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  // 1
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,  // 5
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,  // 5
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,  // 4
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,  // 0

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,  // 3
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,  // 7
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,  // 6
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,  // 6
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,  // 2
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f   // 3
	};

	VertexBuffer vb(vertPos, sizeof(float) * 288);	  // Create vertext buffer
	VertexBufferLayout layout;						  // Create buffer layout
	// Setup layout
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	// Bind vb and layout to va
	m_VA.SetupArray(vb, layout);

	// Indices
	unsigned int vertIdx[36] = {
		 0,  1,  2,  3,  4,  5,
		 6,  7,  8,  9, 10, 11,
		12, 13, 14, 15, 16, 17,
		18, 19, 20, 21, 22, 23,
		24, 25, 26, 27, 28, 29,
		30, 31, 32, 33, 34, 35
	};
	m_IB.SetData(vertIdx, 36);
}

Model::~Model() {}

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
	// Drawcall
	//glDrawElements(GL_TRIANGLES, m_IB.GetCount(), m_IB.GetIndexType(), nullptr);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}