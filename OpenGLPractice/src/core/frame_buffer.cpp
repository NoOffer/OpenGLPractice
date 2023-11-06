#include "frame_buffer.h"

FrameBuffer::FrameBuffer(int frameW, int frameH, bool rbDepthStencil)
	: m_Width(frameW), m_Height(frameH)
{
	glGenFramebuffers(1, &m_RendererID);

	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

	// Color attachment (texture 2D)
	glGenTextures(1, &m_CTexID);
	glBindTexture(GL_TEXTURE_2D, m_CTexID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, frameW, frameH, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_CTexID, 0);

	// Depth-stencil attachment (texture 2D / render buffer)
	if (rbDepthStencil)
	{
		glGenRenderbuffers(1, &m_DSRBOID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_DSRBOID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, frameW, frameH);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DSRBOID);
		m_DSTexID = 0;
	}
	else
	{
		glGenTextures(1, &m_DSTexID);
		glBindTexture(GL_TEXTURE_2D, m_DSTexID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, frameW, frameH, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DSTexID, 0);
		m_DSRBOID = 0;
	}

	// Check framebuffer status
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		LogWarning("Frame buffer incomplete");
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_RendererID);
	glDeleteTextures(1, &m_CTexID);
	glDeleteTextures(1, &m_DSTexID);
	glDeleteRenderbuffers(1, &m_DSRBOID);
}

void FrameBuffer::BindR() const
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_RendererID);
}

void FrameBuffer::UnbindR() const
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

void FrameBuffer::BindW() const
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_RendererID);
}

void FrameBuffer::UnbindW() const
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void FrameBuffer::BindRW() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
}

void FrameBuffer::UnbindRW() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
