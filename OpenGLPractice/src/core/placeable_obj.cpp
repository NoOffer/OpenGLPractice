#include "placeable_obj.h"

PlaceableObj::PlaceableObj()
{
	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	m_ModelMatrix = glm::mat4(1.0f);
	m_ModelMatrixAvailable = false;
}

glm::mat4 PlaceableObj::GetModelMatrix()
{
	if (!m_ModelMatrixAvailable)
	{
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 rotation = glm::mat4(1.0f);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Scale);
		m_ModelMatrix = translation * rotation * scale;

		m_ModelMatrixAvailable = true;
	}
	return m_ModelMatrix;
}