#include "camera.h"

Camera::Camera(float fov, glm::uvec2 resolution)
	: m_FOV(fov), m_Resolution(resolution),
	m_ViewMatrixAvailable(false), m_ProjMatrixAvailable(false)
{
	m_ViewMatrix = glm::mat4();
	m_ProjMatrix = glm::mat4();
}

Camera::~Camera() {}

glm::mat4 Camera::GetViewMatrix()
{
	if (!m_ViewMatrixAvailable)
	{
		glm::vec3 backward(glm::normalize(m_Position));  // By convention the z axis of camera points backward
		glm::vec3 right(glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), backward)));
		glm::vec3 upward(glm::normalize(glm::cross(backward, right)));
		m_ViewMatrix = glm::lookAt(m_Position, glm::vec3(0.0f, 0.0f, 0.0f), upward);
		m_ViewMatrixAvailable = true;
	}
	return m_ViewMatrix;
	//return glm::mat4(
	//	right.x, upward.x, forward.x, m_Position.x,
	//	right.y, upward.y, forward.y, m_Position.y,
	//	right.z, upward.z, forward.z, m_Position.z,
	//	0.0f, 0.0f, 0.0f, 0.0f
	//);
}

glm::mat4 Camera::GetProjMatrix()
{
	if (!m_ProjMatrixAvailable)
	{
		m_ProjMatrix = glm::perspective(glm::radians(m_FOV), (float)m_Resolution.x / (float)m_Resolution.y, 0.1f, 100.0f);
	}
	//return glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
	return m_ProjMatrix;
}

void Camera::Update(float deltaTime) {}
