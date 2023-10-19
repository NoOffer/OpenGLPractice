#pragma once

#include "index_buffer.h"
#include "vertex_array.h"
#include "cube_map.h"
#include "shader.h"

class Skybox
{
public:
	Skybox(const CubeMap& cubeMap);
	~Skybox();

	void Render(mat4 viewMat, mat4 projMat);

private:
	IndexBuffer m_IB;
	VertexArray m_VA;
	Shader m_Shader;
	CubeMap m_CubeMap;
};

