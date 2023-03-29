#pragma once

#include "placeable_obj.h"

class Camera : public PlaceableObj
{
public:
	Camera(float fov, glm::uvec2 resolution);
	~Camera();

	inline void SetPosition(glm::vec3 v)  override { PlaceableObj::SetPosition(v); m_ViewMatrixAvailable = false; }
	inline void SetPosition(float x, float y, float z) override
	{
		PlaceableObj::SetPosition(x, y, z); m_ViewMatrixAvailable = false;
	}
	inline void Translate(glm::vec3 v) override { PlaceableObj::Translate(v); m_ViewMatrixAvailable = false; }
	inline void Translate(float x, float y, float z) override { PlaceableObj::Translate(x, y, z); m_ViewMatrixAvailable = false; }

	inline void SetRotation(glm::vec3 v)  override { PlaceableObj::SetRotation(v); m_ViewMatrixAvailable = false; }
	inline void SetRotation(float x, float y, float z)  override
	{
		PlaceableObj::SetRotation(x, y, z); m_ViewMatrixAvailable = false;
	}
	inline void Rotate(glm::vec3 v) override { PlaceableObj::Rotate(v); m_ViewMatrixAvailable = false; }
	inline void Rotate(float x, float y, float z) override { PlaceableObj::Rotate(x, y, z); m_ViewMatrixAvailable = false; }

	inline void SetScale(glm::vec3 v) override {}
	inline void SetScale(float x, float y, float z) override {}
	inline void Scale(glm::vec3 v) override {}
	inline void Scale(float t) override {}
	inline void Scale(float x, float y, float z) override {}

	inline void SetFOV(float fov) { m_FOV = fov; m_ProjMatrixAvailable = false; }

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjMatrix();

	void Update(float deltaTime);

private:
	float m_FOV;
	glm::uvec2 m_Resolution;

	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjMatrix;
	bool m_ViewMatrixAvailable;
	bool m_ProjMatrixAvailable;
};
