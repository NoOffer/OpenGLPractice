#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Pos;

//uniform sampler2D u_Texture;

void main()
{
	color = vec4(v_Pos, 1);
};