#version 330 core

layout(location = 0) in vec2 a_Position;

out vec2 v_TexCoords;

void main()
{
	v_TexCoords = a_Position;
	gl_Position = vec3(a_Position, 0.0f);
}