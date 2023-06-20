#pragma once

#include "placeable_obj.h"

class PointLight : public PlaceableObj
{
public:
	PointLight(vec3 color);
	~PointLight();

	inline vec3 GetColor() { return m_Color; }

private:
	vec3 m_Color;
};

