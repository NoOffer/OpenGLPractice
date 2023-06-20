#include "camera.h"

Camera::Camera(float fov, vec2i resolution)
	: m_FOV(fov), m_Resolution(resolution),
	m_ViewMatrixAvailable(false), m_ProjMatrixAvailable(false)
{
	m_ViewMatrix = mat4();
	m_ProjMatrix = mat4();
}

Camera::~Camera() {}

mat4 Camera::GetViewMatrix()
{
	if (!m_ViewMatrixAvailable)
	{
		vec3 z(normalize(m_Position));  // By convention the z axis of camera points backward
		vec3 x(normalize(cross(vec3(0.0f, 1.0f, 0.0f), z)));
		vec3 y(normalize(cross(z, x)));

		mat4 minv(
			x.x, x.y, x.z, 0.0f,
			y.x, y.y, y.z, 0.0f,
			z.x, z.y, z.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		mat4 tr(1.0f);
		tr[0][3] = -m_Position.x;
		tr[1][3] = -m_Position.y;
		tr[2][3] = -m_Position.z;

		m_ViewMatrix = mul(minv, tr);

		m_ViewMatrixAvailable = true;
	}
	return m_ViewMatrix;
}

mat4 Camera::GetProjMatrix()
{
	if (!m_ProjMatrixAvailable)
	{
		// Perspective
		float nHeight = tan(m_FOV / 2);
		float nWidth = nHeight / m_Resolution.y * m_Resolution.x;
		float m22 = (0.1f + 100.0f) / (0.1f - 100.0f);
		float m23 = (2 * 0.1f * 100.0f) / (0.1f - 100.0f);
		m_ProjMatrix = mat4(
			1 / nWidth, 0.0f, 0.0f, 0.0f,
			0.0f, 1 / nHeight, 0.0f, 0.0f,
			0.0f, 0.0f, m22, m23,
			0.0f, 0.0f, -1.0f, 0.0f
		);

		m_ProjMatrixAvailable = true;
	}
	//return ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
	return m_ProjMatrix;
}

void Camera::Update(float deltaTime) {}
