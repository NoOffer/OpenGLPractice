#include "Camera.h"

Camera::Camera(float fov, glm::uvec2 resolution) : m_FOV(fov), m_Resolution(resolution) {}

Camera::~Camera() {}

glm::mat4 Camera::GetProjMatrix()
{
	//return glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
	return glm::perspective(glm::radians(m_FOV), (float)m_Resolution.x / (float)m_Resolution.y, 0.1f, 100.0f);
}

glm::mat4 Camera::GetViewMatrix()
{
	glm::vec3 backward(glm::normalize(m_Position));  // By convention the z axis of camera points backward
	glm::vec3 right(glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), backward)));
	glm::vec3 upward(glm::normalize(glm::cross(backward, right)));
	return glm::lookAt(m_Position, glm::vec3(0.0f, 0.0f, 0.0f), upward);
	//return glm::mat4(
	//	right.x, upward.x, forward.x, m_Position.x,
	//	right.y, upward.y, forward.y, m_Position.y,
	//	right.z, upward.z, forward.z, m_Position.z,
	//	0.0f, 0.0f, 0.0f, 0.0f
	//);
}

void Camera::Update(float deltaTime) {}
