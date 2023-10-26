#include "post_process.h"

static float vertices[8] = {
	-1.0f, -1.0f,
	-1.0f,  1.0f,
	 1.0f, -1.0f,
	 1.0f,  1.0f
};

static unsigned int indices[6] =
{
	0, 1, 2,
	1, 3, 2
};

PostProcess::PostProcess(unsigned int srcTexID) :
	m_IB(IndexBuffer(indices, 6)),
	m_Shader(
		"res/shaders/SkyboxVert.shader",
		"res/shaders/SkyboxFrag.shader"
	),
	m_SrcTexID(srcTexID)
{
	m_VA.Bind();
	// Vertices
	VertexBuffer vb(vertices, sizeof(float) * 8);  // Create vertext buffer
	VertexBufferLayout layout;						// Create buffer layout
	// Setup layout
	layout.Push<float>(2);  // Vertex position
	// Bind vb and layout to va
	m_VA.SetupArray(vb, layout);
	m_VA.Unbind();
}

PostProcess::~PostProcess() {}

void PostProcess::Render()
{
	m_IB.Bind();
	m_VA.Bind();
	m_Shader.Bind();

	m_Shader.SetUniform1i("u_Texture", m_SrcTexID);

	glDrawElements(GL_TRIANGLES, m_IB.GetCount(), GL_UNSIGNED_INT, indices);
}
