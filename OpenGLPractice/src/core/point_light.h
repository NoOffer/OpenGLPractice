#pragma once

#include "placeable_obj.h"

class PointLight : public PlaceableObj
{
public:
	inline PointLight(vec3 color) : m_Color(color) {}
	inline ~PointLight() {}

	inline vec3 GetColor() { return m_Color; }

private:
	vec3 m_Color;
};

