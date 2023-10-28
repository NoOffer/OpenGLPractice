#pragma once

#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"
#include "frame_buffer.h"

class PostProcess
{
public:
	PostProcess(unsigned int srcTexID);
	~PostProcess();

	void Render(FrameBuffer& srcFBO);

private:
	IndexBuffer m_IB;
	VertexArray m_VA;
	Shader m_Shader;
};

