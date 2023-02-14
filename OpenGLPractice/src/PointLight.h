#pragma once

#include "PlaceableObj.h"

class PointLight : public PlaceableObj
{
public:
	PointLight(glm::vec3 color);
	~PointLight();

	inline glm::vec3 GetColor() { return m_Color; }

private:
	glm::vec3 m_Color;
};

