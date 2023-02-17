#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

out vec3 v_PosWS;
out vec3 v_Normal;
out vec2 v_Texcoord;

uniform mat4 u_Matrix_VP;
uniform mat4 u_Matrix_M;
uniform mat3 u_Matrix_M_Normal;

void main()
{
	gl_Position = u_Matrix_M * vec4(position, 1.0);
	v_PosWS = gl_Position.xyz;
	gl_Position = u_Matrix_VP * gl_Position;

	v_Normal = normalize(u_Matrix_M_Normal * normal);
	v_Texcoord = texcoord;
};