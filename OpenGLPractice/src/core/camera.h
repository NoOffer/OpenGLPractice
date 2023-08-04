#pragma once

#include "placeable_obj.h"

class Camera : public PlaceableObj
{
public:
	Camera(float fov, vec2i resolution);
	~Camera();

	inline void SetPosition(vec3 v)  override { PlaceableObj::SetPosition(v); m_ViewMatrixAvailable = false; }
	inline void SetPosition(float x, float y, float z) override
	{
		PlaceableObj::SetPosition(x, y, z); m_ViewMatrixAvailable = false;
	}
	inline void Translate(vec3 v) override { PlaceableObj::Translate(v); m_ViewMatrixAvailable = false; }
	inline void Translate(float x, float y, float z) override { PlaceableObj::Translate(x, y, z); m_ViewMatrixAvailable = false; }

	inline void SetRotation(vec3 v)  override { PlaceableObj::SetRotation(v); m_ViewMatrixAvailable = false; }
	inline void SetRotation(float x, float y, float z)  override
	{
		PlaceableObj::SetRotation(x, y, z); m_ViewMatrixAvailable = false;
	}
	inline void Rotate(vec3 v) override { PlaceableObj::Rotate(v); m_ViewMatrixAvailable = false; }
	inline void Rotate(float x, float y, float z) override { PlaceableObj::Rotate(x, y, z); m_ViewMatrixAvailable = false; }

	inline void SetScale(vec3 v) override {}
	inline void SetScale(float x, float y, float z) override {}
	inline void Scale(vec3 v) override {}
	inline void Scale(float t) override {}
	inline void Scale(float x, float y, float z) override {}

	inline void SetFOV(float fov) { m_FOV = fov; m_ProjMatrixAvailable = false; }

	mat4 GetViewMatrix();
	mat4 GetProjMatrix();

protected:
	float m_FOV;
	vec2i m_Resolution;

	mat4 m_ViewMatrix;
	mat4 m_ProjMatrix;
	bool m_ViewMatrixAvailable;
	bool m_ProjMatrixAvailable;
};
