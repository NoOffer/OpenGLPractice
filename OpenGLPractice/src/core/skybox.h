#pragma once

#include "index_buffer.h"
#include "vertex_array.h"
#include "cube_map.h"
#include "shader.h"

class Skybox
{
public:
	Skybox(
		const std::string& pos_x_path,
		const std::string& neg_x_path,
		const std::string& pos_y_path,
		const std::string& neg_y_path,
		const std::string& pos_z_path,
		const std::string& neg_z_path,
		const std::string& name = ""
	);
	~Skybox();

	void Render(mat4 viewMat, mat4 projMat);

private:
	IndexBuffer m_IB;
	VertexArray m_VA;
	Shader m_Shader;
	CubeMap m_CubeMap;
};

