#pragma once

#include "math/vector.h"

class DirectionalLight
{
public:
	inline DirectionalLight(vec3 dir, vec3 color) : m_Dir(normalize(dir)), m_Color(color) {}
	inline ~DirectionalLight() {}

	inline vec3 GetDirection() { return m_Dir; }
	inline vec3 GetColor() { return m_Color; }

private:
	vec3 m_Dir;
	vec3 m_Color;
};

