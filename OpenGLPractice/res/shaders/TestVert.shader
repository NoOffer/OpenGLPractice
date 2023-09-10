#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

out vec3 v_PosWS;
out vec3 v_Normal;
out vec2 v_TexCoord;

uniform mat4 u_Matrix_VP;
uniform mat4 u_Matrix_M;
uniform mat3 u_Matrix_M_Normal;

void main()
{
	gl_Position = u_Matrix_M * vec4(a_Position, 1.0);
	v_PosWS = gl_Position.xyz;
	gl_Position = u_Matrix_VP * gl_Position;

	v_Normal = normalize(u_Matrix_M_Normal * a_Normal);
	v_TexCoord = a_TexCoord;
};