#include "placeable_obj.h"

PlaceableObj::PlaceableObj()
{
	m_Position = vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = vec3(0.0f, 0.0f, 0.0f);
	m_Scale = vec3(1.0f, 1.0f, 1.0f);

	m_ModelMatrix = mat4(1.0f);
	m_NormalMatrix = mat4(1.0f);
	m_ModelMatrixAvailable = false;
}

mat4 PlaceableObj::GetModelMatrix()
{
	if (!m_ModelMatrixAvailable)
	{
		// Model vertex transformation matrix
		mat4 translationMat = TranslateMat(m_Position);
		mat4 rotationMat = RotateMat(m_Rotation);
		mat4 scaleMat = ScaleMat(m_Scale);
		//m_ModelMatrix = TranslateMat(mul(rotationMat, scaleMat), m_Position);
		m_ModelMatrix = mul(mul(translationMat, rotationMat), scaleMat);

		// Model normal transformation matrix
		translationMat = TranslateMat(-m_Position);
		vec3 inversedScale;
		inversedScale.x = 1 / m_Scale.x;
		inversedScale.y = 1 / m_Scale.y;
		inversedScale.z = 1 / m_Scale.z;
		scaleMat = ScaleMat(inversedScale);
		//m_NormalMatrix = TranslateMat(mul(scaleMat, Transpose(rotationMat)), -m_Position);
		m_NormalMatrix = mul(mul(scaleMat, Transpose(rotationMat)), translationMat);

		m_ModelMatrixAvailable = true;
	}
	return m_ModelMatrix;
}

mat4 PlaceableObj::GetNormalMatrix()
{
	if (!m_ModelMatrixAvailable)
	{
		GetModelMatrix();
	}
	return m_NormalMatrix;
}