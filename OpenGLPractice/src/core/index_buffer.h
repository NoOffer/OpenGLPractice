#pragma once

#include <glad/glad.h>

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	void SetData(const unsigned int* data, unsigned int count);
	void SetData(const unsigned short* data, unsigned int count);

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; };
	inline GLenum GetIndexType() const { return m_IndexType; };
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
	GLenum m_IndexType;
};