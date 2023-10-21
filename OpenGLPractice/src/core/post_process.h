#pragma once

#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"

class PostProcess
{
public:
	PostProcess();
	~PostProcess();

private:
	IndexBuffer m_IB;
	VertexArray m_VA;
	//Shader m_Shader;
};
