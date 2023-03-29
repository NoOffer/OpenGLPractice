#pragma once

#include "placeable_obj.h"
#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

class Model : public PlaceableObj
{
public:
	Model();
	~Model();

	inline void SetShader(const Shader& shader) { m_Shader = shader; }

	void Bind();
	void Unbind();

	void Draw();

private:
	VertexArray m_VA;
	IndexBuffer m_IB;
	Shader m_Shader;
};

