#include "PlaceableObj.h"

PlaceableObj::PlaceableObj()
{
	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	m_RotationMat = glm::mat4(1.0f);
}

void PlaceableObj::Translate(float xOffset, float yOffset, float zOffset)
{
	m_Position += glm::vec3(xOffset, yOffset, zOffset);
}

void PlaceableObj::Rotate(float angle, glm::vec3 axis)
{
	m_RotationMat = glm::rotate(m_RotationMat, glm::radians(angle), axis);
}

void PlaceableObj::Scale(float xScale, float yScale, float zScale)
{
	m_Scale *= glm::vec3(xScale, yScale, zScale);
}