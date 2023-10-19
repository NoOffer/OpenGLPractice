#include "skybox.h"

static float vertices[24] = {
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f
};

static unsigned int indices[36] =
{
	// X-
	0, 1, 2,
	2, 1, 3,
	// Y- 
	1, 7, 3,
	1, 5, 7,
	// Z- 
	2, 3, 7,
	2, 7, 6,
	// X+ 
	4, 7, 5,
	4, 6, 7,
	// Y+ 
	2, 4, 0,
	2, 6, 4,
	// Z+ 
	0, 4, 1,
	4, 5, 1
};

Skybox::Skybox(const CubeMap& cubeMap) :
	m_IB(IndexBuffer(indices, 36)),
	m_Shader(
		"res/shaders/SkyboxVert.shader",
		"res/shaders/SkyboxFrag.shader"
	),
	m_CubeMap(cubeMap)
{
	m_VA.Bind();
	// Vertices
	VertexBuffer vb(vertices, sizeof(float) * 24);  // Create vertext buffer
	VertexBufferLayout layout;						// Create buffer layout
	// Setup layout
	layout.Push<float>(3);  // Vertex position
	// Bind vb and layout to va
	m_VA.SetupArray(vb, layout);
	m_VA.Unbind();

	m_Shader.SetUniform1i("u_SkyboxMap", 0);
}

Skybox::~Skybox() {}

void Skybox::Render(mat4 projMatrix, mat4 viewMatrix)
{
	viewMatrix[0][3] = 0.0f;
	viewMatrix[1][3] = 0.0f;
	viewMatrix[2][3] = 0.0f;
	m_Shader.SetUniformMat4f("u_MatrixVP", mul(projMatrix, viewMatrix));

	glCullFace(GL_BACK);
	// Disable depth write
	glDepthMask(GL_FALSE);
	// Set depth test to less/equal
	glDepthFunc(GL_LEQUAL);

	m_IB.Bind();
	m_VA.Bind();
	m_Shader.Bind();
	m_CubeMap.Bind();

	glDrawElements(GL_TRIANGLES, m_IB.GetCount(), GL_UNSIGNED_INT, indices);
	//glDrawArrays(GL_TRIANGLES, 0, m_IB.GetCount());

	m_IB.Unbind();
	m_VA.Unbind();
	m_Shader.Unbind();
	m_CubeMap.Unbind();

	// Re-enable depth write
	glDepthMask(GL_TRUE);
	// Set depth test back to less
	glDepthFunc(GL_LESS);
}
