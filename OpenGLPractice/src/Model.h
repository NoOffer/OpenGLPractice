#pragma once

#include "PlaceableObj.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Model : public PlaceableObj
{
public:
	Model();
	~Model();

	glm::mat4 GetModelMatrix();

	inline void SetShader(Shader& shader) { m_Shader = shader; }

	void Bind();
	void Unbind();

	void Draw();

private:
	VertexArray m_VA;
	IndexBuffer m_IB;
	Shader m_Shader;
};

