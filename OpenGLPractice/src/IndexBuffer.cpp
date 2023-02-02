#include "IndexBuffer.h"

#include <GLAD/glad.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_Count(count), m_IndexType(GL_UNSIGNED_INT)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(const unsigned short* data, unsigned int count)
	: m_Count(count), m_IndexType(GL_UNSIGNED_SHORT)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * count, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
