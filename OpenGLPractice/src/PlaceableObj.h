#pragma once

#include "glm/gtc/matrix_transform.hpp"

class PlaceableObj
{
public:
	PlaceableObj();
	virtual ~PlaceableObj() {}

	inline void Translate(glm::vec3 v) { m_Position += v; }
	inline void Scale(glm::vec3 v) { m_Scale *= v; }
	void Translate(float xOffset, float yOffset, float zOffset);
	void Rotate(float angle, glm::vec3 axis);
	void Scale(float xScale, float yScale, float zScale);

protected:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	glm::mat4 m_RotationMat;
};

