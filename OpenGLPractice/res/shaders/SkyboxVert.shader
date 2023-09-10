#version 330 core

layout(location = 0) in vec3 a_Position;

out vec3 v_TexCoords;

uniform mat4 u_Matrix_V;
uniform mat4 u_Matrix_P;

void main()
{
	v_TexCoords = a_Position;
	gl_Position = u_Matrix_P * u_Matrix_V * vec4(a_Position, 1.0);
}