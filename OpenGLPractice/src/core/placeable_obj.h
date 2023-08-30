#pragma once

#include "matrix.h"

enum class Space
{
	Local, World
};

class PlaceableObj
{
public:
	PlaceableObj();
	virtual ~PlaceableObj() {}

	inline vec3 GetPosition() { return m_Position; }

	virtual inline void SetPosition(vec3 v) { m_Position = v; m_ModelMatrixAvailable = false; }
	virtual inline void SetPosition(float x, float y, float z) { m_Position = vec3(x, y, z); m_ModelMatrixAvailable = false; }
	virtual inline void Translate(vec3 v) { m_Position += v; m_ModelMatrixAvailable = false; }
	virtual inline void Translate(float x, float y, float z) { m_Position += vec3(x, y, z); m_ModelMatrixAvailable = false; }

	virtual inline void SetRotation(vec3 v) { m_Rotation = v; m_ModelMatrixAvailable = false; }
	virtual inline void SetRotation(float x, float y, float z) { m_Rotation = vec3(x, y, z); m_ModelMatrixAvailable = false; }
	virtual inline void Rotate(vec3 v) { m_Rotation += v; m_ModelMatrixAvailable = false; }
	virtual inline void Rotate(float x, float y, float z) { m_Rotation += vec3(x, y, z); m_ModelMatrixAvailable = false; }

	virtual inline void SetScale(vec3 v) { m_Scale = v; m_ModelMatrixAvailable = false; }
	virtual inline void SetScale(float x, float y, float z) { m_Scale = vec3(x, y, z); m_ModelMatrixAvailable = false; }
	virtual inline void Scale(vec3 v) { m_Scale *= v; m_ModelMatrixAvailable = false; }
	virtual inline void Scale(float t) { m_Scale *= t; m_ModelMatrixAvailable = false; }
	virtual inline void Scale(float x, float y, float z) { m_Scale *= vec3(x, y, z); m_ModelMatrixAvailable = false; }

	mat4 GetModelMatrix();
	mat4 GetNormalMatrix();

protected:
	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;

	mat4 m_ModelMatrix;
	mat4 m_NormalMatrix;
	bool m_ModelMatrixAvailable;
};

