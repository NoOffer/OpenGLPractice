#version 330 core

out vec4 color;

in vec3 v_TexCoords;

uniform samplerCube u_SkyboxMap;

void main()
{
	color = texture(u_SkyboxMap, v_TexCoords);
	//color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}