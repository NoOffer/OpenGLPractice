#pragma once

#include "glm/glm.hpp"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Model
{
public:
	Model();
	~Model();

	inline void Translate(glm::vec3 v) { m_Position += v; }
	inline void Rotate(glm::vec3 v) { m_Rotation += v; }
	inline void Scale(glm::vec3 v) { m_Scale *= v; }
	void Translate(float xOffset, float yOffset, float zOffset);
	void Rotate(float xOffset, float yOffset, float zOffset);
	void Scale(float xScale, float yScale, float zScale);
	glm::mat4 GetModelMatrix();

	inline void SetShader(Shader& shader) { m_Shader = shader; }

	void Bind();
	void Unbind();

	void Draw();

private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	VertexArray m_VA;
	IndexBuffer m_IB;
	Shader m_Shader;
};

