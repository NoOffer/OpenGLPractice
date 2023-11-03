#version 330 core

out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	color = texture(u_Texture, v_TexCoord);

	float invGamma = 1.0 / 2.2;
	color.rgb = pow(color.rgb, vec3(invGamma));
}