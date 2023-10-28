#include "post_process.h"

static float vertices[16] = {
	-1.0f, -1.0f, 0.0f, 0.0f,
	-1.0f,  1.0f, 0.0f, 1.0f,
	 1.0f, -1.0f, 1.0f, 0.0f,
	 1.0f,  1.0f, 1.0f, 1.0f
};

static unsigned int indices[6] =
{
	0, 2, 1,
	1, 2, 3
};

PostProcess::PostProcess(unsigned int srcTexID) :
	m_IB(IndexBuffer(indices, 6)),
	m_Shader(
		"res/shaders/PPVert.shader",
		"res/shaders/PPFrag.shader"
	)
{
	m_VA.Bind();
	// Vertices
	VertexBuffer vb(vertices, sizeof(float) * 16);  // Create vertext buffer
	VertexBufferLayout layout;						// Create buffer layout
	// Setup layout
	layout.Push<float>(2);  // Vertex position
	layout.Push<float>(2);  // Texture UV
	// Bind vb and layout to va
	m_VA.SetupArray(vb, layout);
	m_VA.Unbind();
}

PostProcess::~PostProcess() {}

void PostProcess::Render(FrameBuffer& srcFBO)
{
	unsigned int width = srcFBO.GetWidth();
	unsigned int height = srcFBO.GetHeight();
	FrameBuffer tmpFBO(width, height);

	srcFBO.BindR();
	tmpFBO.BindW();
	glBlitFramebuffer(
		0, 0, width, height,
		0, 0, width, height,
		GL_COLOR_BUFFER_BIT, GL_NEAREST
	);
	srcFBO.BindW();

	glCullFace(GL_BACK);
	// Disable depth write
	glDepthMask(GL_FALSE);
	// Set depth test to always
	glDepthFunc(GL_ALWAYS);

	m_IB.Bind();
	m_VA.Bind();
	m_Shader.Bind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tmpFBO.GetTexID());

	m_Shader.SetUniform1i("u_Texture", 0);

	glDrawElements(GL_TRIANGLES, m_IB.GetCount(), GL_UNSIGNED_INT, indices);

	//glBindTexture(GL_TEXTURE_2D, 0);

	m_IB.Unbind();
	m_VA.Unbind();
	m_Shader.Unbind();

	// Re-enable depth write
	glDepthMask(GL_TRUE);
	// Set depth test back to less
	glDepthFunc(GL_LESS);
}
