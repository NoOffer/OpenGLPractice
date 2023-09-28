#include "vector.h"

float length(vec2 v)
{
	return std::sqrt(v.x * v.x + v.y * v.y);
}

float length(vec3 v)
{
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float length(vec4 v)
{
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

vec2 normalize(vec2 v)
{
	return v / length(v);
}

vec3 normalize(vec3 v)
{
	float l = length(v);
	if (l)
	{
		return v / l;
	}
	return vec3();
}

vec4 normalize(vec4 v)
{
	float l = length(v);
	if (l)
	{
		return v / l;
	}
	return vec4();
}

float dot(vec2 v1, vec2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float dot(vec3 v1, vec3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float dot(vec4 v1, vec4 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

float cross(vec2 v1, vec2 v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

vec3 cross(vec3 v1, vec3 v2)
{
	return vec3{ v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
}