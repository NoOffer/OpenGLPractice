#include "index_buffer.h"

#include <GLAD/glad.h>

IndexBuffer::IndexBuffer()
	: m_Count(0), m_IndexType(GL_UNSIGNED_INT)
{
	glGenBuffers(1, &m_RendererID);
}

void IndexBuffer::SetData(const unsigned int* data, unsigned int count)
{
	m_Count = count;
	m_IndexType = GL_UNSIGNED_INT;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, data, GL_STATIC_DRAW);
}

void IndexBuffer::SetData(const unsigned short* data, unsigned int count)
{
	m_Count = count;
	m_IndexType = GL_UNSIGNED_SHORT;
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
