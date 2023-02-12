#include "Camera.h"

Camera::Camera() {}

Camera::~Camera() {}

glm::mat4 Camera::GetViewMatrix()
{
	glm::vec3 forward(glm::normalize(m_Position));
	glm::vec3 right(glm::cross(glm::vec3(1.0f, 1.0f, 1.0f), forward));
	glm::vec3 upward(glm::cross(forward, right))
	return glm::mat4();
}
