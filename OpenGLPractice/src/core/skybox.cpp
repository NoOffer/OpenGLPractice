#include "skybox.h"

VertexArray Skybox::s_VA;
CubeMap Skybox::s_CubeMap;

void Skybox::Init()
{
	float vertices[24] = {
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f
	};

	unsigned int indices[36] = {
		// X-
		1, 3, 2,
		3, 4, 2,
		// Y-
		2, 4, 8,
		2, 8, 6,
		// Z-
		3, 8, 4,
		3, 7, 8,
		// X+
		5, 6, 8,
		5, 8, 7,
		// Y+
		3, 1, 5,
		3, 5, 7,
		// Z+
		1, 2, 5,
		5, 2, 6
	};

	s_IB = IndexBuffer(indices, sizeof(int) * 36);

	s_VA.Bind();
	// Vertices
	VertexBuffer vb(vertices, sizeof(float) * 24);  // Create vertext buffer
	VertexBufferLayout layout;						// Create buffer layout
	// Setup layout
	layout.Push<float>(3);  // Vertex position
	// Bind vb and layout to va
	s_VA.SetupArray(vb, layout);
	s_VA.Unbind();
}

void Skybox::Render()
{
	// Enable culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	// Enable depth test
	glDisable(GL_DEPTH_TEST);

	s_IB.Bind();
	s_VA.Bind();

	// Render something

	s_IB.Unbind();
	s_VA.Unbind();

	// Restore culling setting
	glCullFace(GL_BACK);
	// Re-enable depth test
	glEnable(GL_DEPTH_TEST);
}
