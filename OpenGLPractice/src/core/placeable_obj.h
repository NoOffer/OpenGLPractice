#pragma once

#include "glm/gtc/matrix_transform.hpp"

enum class Space
{
	Local, World
};

class PlaceableObj
{
public:
	PlaceableObj();
	virtual ~PlaceableObj() {}

	inline glm::vec3 GetPosition() { return m_Position; }

	virtual inline void SetPosition(glm::vec3 v) { m_Position = v; m_ModelMatrixAvailable = false; }
	virtual inline void SetPosition(float x, float y, float z) { m_Position = glm::vec3(x, y, z); m_ModelMatrixAvailable = false; }
	virtual inline void Translate(glm::vec3 v) { m_Position += v; m_ModelMatrixAvailable = false; }
	virtual inline void Translate(float x, float y, float z) { m_Position += glm::vec3(x, y, z); m_ModelMatrixAvailable = false; }

	virtual inline void SetRotation(glm::vec3 v) { m_Rotation = v; m_ModelMatrixAvailable = false; }
	virtual inline void SetRotation(float x, float y, float z) { m_Rotation = glm::vec3(x, y, z); m_ModelMatrixAvailable = false; }
	virtual inline void Rotate(glm::vec3 v) { m_Rotation += v; m_ModelMatrixAvailable = false; }
	virtual inline void Rotate(float x, float y, float z) { m_Rotation += glm::vec3(x, y, z); m_ModelMatrixAvailable = false; }

	virtual inline void SetScale(glm::vec3 v) { m_Scale = v; m_ModelMatrixAvailable = false; }
	virtual inline void SetScale(float x, float y, float z) { m_Scale = glm::vec3(x, y, z); m_ModelMatrixAvailable = false; }
	virtual inline void Scale(glm::vec3 v) { m_Scale *= v; m_ModelMatrixAvailable = false; }
	virtual inline void Scale(float t) { m_Scale *= t; m_ModelMatrixAvailable = false; }
	virtual inline void Scale(float x, float y, float z) { m_Scale *= glm::vec3(x, y, z); m_ModelMatrixAvailable = false; }

	glm::mat4 GetModelMatrix();

protected:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	glm::mat4 m_ModelMatrix;
	bool m_ModelMatrixAvailable;
};

