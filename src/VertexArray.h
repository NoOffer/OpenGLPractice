#pragma once

#include "VertexBuffer.h";
#include "VertexBufferLayout.h";

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void SetupArray(const VertexBuffer& vb, const VertexBufferLayout& layout);
};
