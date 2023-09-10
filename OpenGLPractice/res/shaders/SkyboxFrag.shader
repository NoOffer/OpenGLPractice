#version 330 core

out vec4 color;

in vec3 v_TexCoords;

uniform samplerCube u_Skybox_Map;

void main()
{
	color = texture(u_Skybox_Map, v_TexCoords);
}