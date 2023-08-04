#include "main_camera.h"

//MainCamera MainCamera::s_Instance();

MainCamera& MainCamera::GetInstance()
{
	static MainCamera s_Instance;
	return s_Instance;
}

void MainCamera::Init(float fov, vec2i resolution, vec3 pos)
{
	m_Center = vec3(0);
	m_Radius = std::max(length(pos), 0.01f);

	m_Pitch = asin(pos.y / m_Radius);
	m_Yaw = -atan(pos.x / (pos.z == 0 ? 0.001f : pos.z));
	if (pos.x < 0) m_Yaw += 3.14f;
	if (pos.x == 0 && pos.z > 0) m_Yaw = 3.14f;

	m_FOV = fov;
	m_Resolution = resolution;
	SetPosition(pos);
}

void MainCamera::Pitch(float theta)
{
	m_Pitch += theta;
	m_Pitch = std::max(std::min(m_Pitch, 1.57f), -1.57f);

	vec3 p = GetPosition() - m_Center;
	p *= m_Radius * cos(m_Pitch) / sqrt(p.x * p.x + p.z * p.z);
	p.y = m_Radius * sin(m_Pitch);
	SetPosition(p + m_Center);
}

void MainCamera::Yaw(float theta)
{
	m_Yaw += theta;
	if (m_Yaw > 3.14f) m_Yaw -= 6.28f;
	else if (m_Yaw < -3.14f) m_Yaw += 6.28f;

	vec3 p = GetPosition() - m_Center;
	float hR = -abs(m_Radius * cos(m_Pitch));
	p.x = hR * sin(m_Yaw);
	p.z = hR * cos(m_Yaw);
	SetPosition(p + m_Center);
}

void MainCamera::IncreaseRadius(float dr)
{
	m_Radius = std::max(m_Radius + std::sqrt(m_Radius) * dr * 1.2f, 0.001f);

	vec3 p = GetPosition() - m_Center;
	p *= m_Radius / length(p);
	SetPosition(p + m_Center);
}

void MainCamera::DecreaseRadius(float dr)
{
	m_Radius = std::max(m_Radius - std::sqrt(m_Radius) * dr * 1.2f, 0.001f);

	vec3 p = GetPosition() - m_Center;
	p *= m_Radius / length(p);
	SetPosition(p + m_Center);
}

void MainCamera::MoveCenter(float dx, float dy)
{
	vec3 z(normalize(m_Center - m_Position));
	vec3 x(normalize(cross(vec3(0.0f, 1.0f, 0.0f), z)));
	vec3 y(normalize(cross(z, x)));

	vec3 moveDist = (x * dx + y * dy) * (m_Radius / 300.0f + 0.1f);
	m_Center += moveDist;
	Translate(moveDist);
}

mat4 MainCamera::GetViewMatrix()
{
	if (!m_ViewMatrixAvailable)
	{
		vec3 z(normalize(m_Position - m_Center));  // By convention the z axis of camera points backward
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

MainCamera::MainCamera() : m_Radius(1), m_Pitch(0), m_Yaw(0), Camera(30, vec2i(500, 500)) {}

MainCamera::~MainCamera() {}
