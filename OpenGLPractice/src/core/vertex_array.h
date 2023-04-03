#pragma once

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void SetupArray(const VertexBuffer& vb, const VertexBufferLayout& layout);

private:
	unsigned int m_RendererID;
};
