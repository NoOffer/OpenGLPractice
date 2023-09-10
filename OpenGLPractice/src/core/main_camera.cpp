#include "main_camera.h"

MainCamera MainCamera::s_Instance;

MainCamera& MainCamera::GetInstance()
{
	return s_Instance;
}

MainCamera& MainCamera::Init(float fov, vec2i resolution, vec3 pos)
{
	s_Instance.m_Center = vec3(0);
	s_Instance.m_Radius = std::max(length(pos), 0.01f);

	s_Instance.m_Pitch = asin(pos.y / s_Instance.m_Radius);
	s_Instance.m_Yaw = -atan(pos.x / (pos.z == 0 ? 0.001f : pos.z));
	if (pos.x < 0) s_Instance.m_Yaw += 3.14f;
	if (pos.x == 0 && pos.z > 0) s_Instance.m_Yaw = 3.14f;

	s_Instance.m_FOV = fov;
	s_Instance.m_Resolution = resolution;

	return s_Instance;
}

vec3 MainCamera::GetPosition()
{
	float x = sin(m_Yaw);
	float z = cos(m_Yaw);
	float hf = abs(m_Radius * cos(m_Pitch));
	x *= hf;
	z *= hf;
	float y = m_Radius * sin(m_Pitch);

	return m_Center + vec3(x, y, z);
}

void MainCamera::Pitch(float theta)
{
	m_Pitch += theta;
	m_Pitch = std::max(std::min(m_Pitch, 1.57f), -1.57f);

	m_ViewMatrixAvailable = false;
}

void MainCamera::Yaw(float theta)
{
	m_Yaw += theta;
	if (m_Yaw > 3.14f) m_Yaw -= 6.28f;
	else if (m_Yaw < -3.14f) m_Yaw += 6.28f;

	m_ViewMatrixAvailable = false;
}

void MainCamera::IncreaseRadius(float dr)
{
	m_Radius = std::max(m_Radius + std::sqrt(m_Radius) * dr * 1.2f, 0.001f);

	m_ViewMatrixAvailable = false;
}

void MainCamera::DecreaseRadius(float dr)
{
	m_Radius = std::max(m_Radius - std::sqrt(m_Radius) * dr * 1.2f, 0.001f);

	m_ViewMatrixAvailable = false;
}

void MainCamera::MoveCenter(float dx, float dy)
{
	vec3 z(normalize(m_Center - GetPosition()));
	vec3 x(normalize(cross(vec3(0.0f, 1.0f, 0.0f), z)));
	vec3 y(normalize(cross(z, x)));

	vec3 moveDist = (x * dx + y * dy) * (m_Radius / 300.0f + 0.1f);
	m_Center += moveDist;

	m_ViewMatrixAvailable = false;
}

mat4 MainCamera::GetViewMatrix()
{
	if (!m_ViewMatrixAvailable)
	{
		vec3 position = GetPosition();
		vec3 z(normalize(position - m_Center));
		vec3 x(normalize(cross(vec3(0.0f, 1.0f, 0.0f), z)));
		vec3 y(normalize(cross(z, x)));

		mat4 minv(
			x.x, x.y, x.z, 0.0f,
			y.x, y.y, y.z, 0.0f,
			z.x, z.y, z.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		mat4 tr(1.0f);
		tr[0][3] = -position.x;
		tr[1][3] = -position.y;
		tr[2][3] = -position.z;

		m_ViewMatrix = mul(minv, tr);

		m_ViewMatrixAvailable = true;
	}
	return m_ViewMatrix;
}

mat4 MainCamera::GetProjMatrix()
{
	if (!m_ProjMatrixAvailable)
	{
		// Perspective
		float nHeight = tan(m_FOV / 2);
		float nWidth = nHeight / m_Resolution.y * m_Resolution.x;
		float m22 = -100.1f / 99.9f;  // (near + far) / (near - far)
		float m23 = -20.0f / 99.9f;  // (2 * near * far) / (near - far)
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

MainCamera::MainCamera()
{
	m_FOV = 30.0f;
	m_Resolution = vec2i(500, 500);

	m_ViewMatrixAvailable = false;
	m_ProjMatrixAvailable = false;

	m_Radius = 1.0f;
	m_Pitch, m_Yaw = 0;
}

MainCamera::~MainCamera() {}
