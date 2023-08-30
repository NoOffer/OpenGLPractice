#include "framebuffer.h"

FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &m_RendererID);

	// Check framebuffer status
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	Log(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_RendererID);
}

void FrameBuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
}

void FrameBuffer::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
