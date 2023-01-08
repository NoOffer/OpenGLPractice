#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::SetupArray(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	glBindVertexArray(m_RendererID);
	vb.Bind();

	std::vector<VertexBufferAttrib> attributes = layout.GetAttrib();
	for (int i = 0; i < attributes.size(); i++) {
		glVertexAttribPointer(i, attributes[i].count, attributes[i].type, GL_FALSE, layout.GetStride(), (const void*)attributes[i].offset);
		glEnableVertexAttribArray(i);
	}
}
