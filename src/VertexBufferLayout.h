#pragma once

#include <vector>
#include <GL/glew.h>

struct VertexBufferAttrib
{
	unsigned int type;    // Variable type: int/float
	unsigned int count;   // Number of int/float
	unsigned int offset;  // Number of bytes from the start of the vertex to the start of this attribute
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferAttrib> m_Attributes;
	unsigned int m_Stride;  // Number of bytes of the vertex (the sum of bytes of all attributes)

public:
	VertexBufferLayout()
		: m_Stride(0)
	{
	}

	template<typename T>
	void Push(unsigned int count)
	{
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Attributes.push_back({ 0x1406, count, m_Stride });
		m_Stride += 4 * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Attributes.push_back({ 0x1405, count, m_Stride });
		m_Stride += 4 * count;
	}

	inline const std::vector<VertexBufferAttrib> GetAttrib() const& { return  m_Attributes; }

	inline const unsigned int GetStride() const& { return  m_Stride; }
};
