#pragma once

#include "PlaceableObj.h"

class Camera : public PlaceableObj
{
public:
	Camera(float fov, glm::uvec2 resolution);
	~Camera();

	inline void SetFOV(float fov) { m_FOV = fov; }

	glm::mat4 GetProjMatrix();
	glm::mat4 GetViewMatrix();

private:
	float m_FOV;
	glm::uvec2 m_Resolution;
};
