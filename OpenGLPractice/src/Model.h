#pragma once

#include "glm/glm.hpp"

#include "VertexArray.h"
#include "IndexBuffer.h"

class Model
{
public:
	Model();
	~Model();

	void Translate(glm::vec3 v);
	void Rotate(glm::vec3 v);
	void Scale(glm::vec3 v);
	glm::mat4 GetModelMatrix();

	void Bind();
	void Unbind();

private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	VertexArray m_VA;
	IndexBuffer m_IB;
};

