#include "main_camera.h"

MainCamera MainCamera::s_Instance;

float MainCamera::s_FOV;
vec2i MainCamera::s_Resolution;

mat4 MainCamera::s_ViewMatrix;
mat4 MainCamera::s_ProjMatrix;
bool MainCamera::s_ViewMatrixAvailable;
bool MainCamera::s_ProjMatrixAvailable;

vec3 MainCamera::s_Center;
float MainCamera::s_Radius;
float MainCamera::s_Pitch, MainCamera::s_Yaw;  // Radian

MainCamera& MainCamera::GetInstance()
{
	return s_Instance;
}

void MainCamera::Init(float fov, vec2i resolution, vec3 pos)
{
	s_Center = vec3(0);
	s_Radius = std::max(length(pos), 0.01f);

	s_Pitch = asin(pos.y / s_Radius);
	s_Yaw = -atan(pos.x / (pos.z == 0 ? 0.001f : pos.z));
	if (pos.x < 0) s_Yaw += 3.14f;
	if (pos.x == 0 && pos.z > 0) s_Yaw = 3.14f;

	s_FOV = fov;
	s_Resolution = resolution;
}

vec3 MainCamera::GetPosition()
{
	float x = sin(s_Yaw);
	float z = cos(s_Yaw);
	float hf = abs(s_Radius * cos(s_Pitch));
	x *= hf;
	z *= hf;
	float y = s_Radius * sin(s_Pitch);

	return s_Center + vec3(x, y, z);
}

void MainCamera::Pitch(float theta)
{
	s_Pitch += theta;
	s_Pitch = std::max(std::min(s_Pitch, 1.57f), -1.57f);

	s_ViewMatrixAvailable = false;
}

void MainCamera::Yaw(float theta)
{
	s_Yaw += theta;
	if (s_Yaw > 3.14f) s_Yaw -= 6.28f;
	else if (s_Yaw < -3.14f) s_Yaw += 6.28f;

	s_ViewMatrixAvailable = false;
}

void MainCamera::IncreaseRadius(float dr)
{
	s_Radius = std::max(s_Radius + std::sqrt(s_Radius) * dr * 1.2f, 0.001f);

	s_ViewMatrixAvailable = false;
}

void MainCamera::DecreaseRadius(float dr)
{
	s_Radius = std::max(s_Radius - std::sqrt(s_Radius) * dr * 1.2f, 0.001f);

	s_ViewMatrixAvailable = false;
}

void MainCamera::MoveCenter(float dx, float dy)
{
	vec3 z(normalize(s_Center - GetPosition()));
	vec3 x(normalize(cross(vec3(0.0f, 1.0f, 0.0f), z)));
	vec3 y(normalize(cross(z, x)));

	vec3 moveDist = (x * dx + y * dy) * (s_Radius / 300.0f + 0.1f);
	s_Center += moveDist;

	s_ViewMatrixAvailable = false;
}

mat4 MainCamera::GetViewMatrix()
{
	if (!s_ViewMatrixAvailable)
	{
		vec3 position = GetPosition();
		vec3 z(normalize(position - s_Center));
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

		s_ViewMatrix = mul(minv, tr);

		s_ViewMatrixAvailable = true;
	}
	return s_ViewMatrix;
}

mat4 MainCamera::GetProjMatrix()
{
	if (!s_ProjMatrixAvailable)
	{
		// Perspective
		float nHeight = tan(s_FOV / 2);
		float nWidth = nHeight / s_Resolution.y * s_Resolution.x;
		float m22 = -100.1f / 99.9f;  // (near + far) / (near - far)
		float m23 = -20.0f / 99.9f;  // (2 * near * far) / (near - far)
		s_ProjMatrix = mat4(
			1 / nWidth, 0.0f, 0.0f, 0.0f,
			0.0f, 1 / nHeight, 0.0f, 0.0f,
			0.0f, 0.0f, m22, m23,
			0.0f, 0.0f, -1.0f, 0.0f
		);

		s_ProjMatrixAvailable = true;
	}
	//return ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
	return s_ProjMatrix;
}

MainCamera::MainCamera()
{
	s_FOV = 30.0f;
	s_Resolution = vec2i(500, 500);

	s_ViewMatrixAvailable = false;
	s_ProjMatrixAvailable = false;

	s_Radius = 1.0f;
	s_Pitch, s_Yaw = 0;
}

MainCamera::~MainCamera() {}
