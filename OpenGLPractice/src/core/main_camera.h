#pragma once

#include "camera.h"

//#include <cmath>

class MainCamera : public Camera
{
public:
	static MainCamera& GetInstance();

	void Init(float fov, vec2i resolution, vec3 pos);

	void Pitch(float theta);
	void Yaw(float theta);
	void IncreaseRadius(float dr);
	void DecreaseRadius(float dr);
	void MoveCenter(float dx, float dy);

	mat4 GetViewMatrix();

private:
	static MainCamera s_Instance;

	MainCamera();
	~MainCamera();

	vec3 m_Center;
	float m_Radius;
	float m_Pitch, m_Yaw;  // Radian

	//Camera m_Cam;
};

