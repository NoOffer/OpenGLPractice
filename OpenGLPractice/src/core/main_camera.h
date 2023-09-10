#pragma once

#include "camera.h"

class MainCamera
{
public:
	static MainCamera& GetInstance();

	static MainCamera& Init(float fov, vec2i resolution, vec3 pos);

	vec3 GetPosition();
	void Pitch(float theta);
	void Yaw(float theta);
	void IncreaseRadius(float dr);
	void DecreaseRadius(float dr);
	void MoveCenter(float dx, float dy);

	mat4 GetViewMatrix();
	mat4 GetProjMatrix();

private:
	static MainCamera s_Instance;

	MainCamera();
	~MainCamera();

	float m_FOV;
	vec2i m_Resolution;

	mat4 m_ViewMatrix;
	mat4 m_ProjMatrix;
	bool m_ViewMatrixAvailable;
	bool m_ProjMatrixAvailable;

	vec3 m_Center;
	float m_Radius;
	float m_Pitch, m_Yaw;  // Radian
};

