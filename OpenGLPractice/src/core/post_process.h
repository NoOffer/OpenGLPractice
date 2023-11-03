#pragma once

#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"
#include "frame_buffer.h"

#include <vector>

class PostProcess
{
public:
	PostProcess(unsigned int srcTexID);
	~PostProcess();

	void AddPostProcess(const std::string ppFragFilepath);

	void Render(FrameBuffer& srcFBO);

private:
	IndexBuffer m_IB;
	VertexArray m_VA;
	std::vector<Shader> m_Shaders;
};

