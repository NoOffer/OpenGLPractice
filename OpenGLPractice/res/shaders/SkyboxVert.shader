#version 330 core

layout(location = 0) in vec3 a_Position;

out vec3 v_TexCoords;

uniform mat4 u_MatrixVP;

void main()
{
	v_TexCoords = a_Position;
	gl_Position = (u_MatrixVP * vec4(a_Position, 1.0)).xyww;
}