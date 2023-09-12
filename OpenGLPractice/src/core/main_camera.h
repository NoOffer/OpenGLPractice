#pragma once

#include "camera.h"

class MainCamera
{
public:
	static MainCamera& GetInstance();

	static void Init(float fov, vec2i resolution, vec3 pos);

	static vec3 GetPosition();
	static void Pitch(float theta);
	static void Yaw(float theta);
	static void IncreaseRadius(float dr);
	static void DecreaseRadius(float dr);
	static void MoveCenter(float dx, float dy);

	static mat4 GetViewMatrix();
	static mat4 GetProjMatrix();

private:
	static MainCamera s_Instance;

	MainCamera();
	~MainCamera();

	static float s_FOV;
	static vec2i s_Resolution;

	static mat4 s_ViewMatrix;
	static mat4 s_ProjMatrix;
	static bool s_ViewMatrixAvailable;
	static bool s_ProjMatrixAvailable;

	static vec3 s_Center;
	static float s_Radius;
	static float s_Pitch, s_Yaw;  // Radian
};

