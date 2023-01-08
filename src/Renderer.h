#pragma once

#include <GL/glew.h>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();

class Renderer
{
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader) const;
	void Clear() const;
};
