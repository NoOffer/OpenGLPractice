#pragma once

#include "vector.h"

struct mat4
{
	// Top-left: [0, 0], top-right: [0, 3]
	float m_Mat[4][4];

	mat4();

	mat4(float a);

	mat4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
	);

	inline float* operator[](int i)
	{
		return &(m_Mat[i][0]);
	}

	mat4 Transpose();
};

struct mat3
{
	// Top-left: [0, 0], top-right: [0, 3]
	float m_Mat[3][3];

	mat3();

	mat3(float a);

	//mat3(
	//	float m00, float m01, float m02,
	//	float m10, float m11, float m12,
	//	float m20, float m21, float m22
	//);

	mat3(mat4 m);

	inline float* operator[](int i)
	{
		return &(m_Mat[i][0]);
	}

	//mat4 Transpose();
};

mat4 Transpose(mat4 m);

mat4 TranslateMat(vec3 translation);
mat4 TranslateMat(mat4 m, vec3 translation);
mat4 TranslateMat(vec4 translation);
mat4 TranslateMat(mat4 m, vec4 translation);
mat4 RotateMat(vec3 angles);
mat4 ScaleMat(vec3 scales);

vec4 mul(mat4 mat, vec4 vec);
mat4 mul(mat4 m1, mat4 m2);

std::ostream& operator<<(std::ostream& ostr, mat4& m);