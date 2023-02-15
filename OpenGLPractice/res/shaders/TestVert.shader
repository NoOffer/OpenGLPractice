#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

out vec3 v_Pos;
out vec3 v_Normal;
out vec2 v_Texcoord;

uniform mat4 u_M;
uniform mat4 u_VP;

void main()
{
	gl_Position = u_VP * u_M * vec4(position, 1.0);
	v_Pos = (u_M * vec4(position, 1.0)).xyz;

	v_Normal = normal;
	v_Texcoord = texcoord;
};