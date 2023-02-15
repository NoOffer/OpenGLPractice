#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Pos;
in vec3 v_Normal;
in vec2 v_Texcoord;

uniform sampler2D u_Texture;
uniform vec3 u_LightPos;
uniform vec3 u_LightColor;
uniform float u_AmbientFactor;

void main()
{
	vec3 normal = normalize(v_Normal);
	vec3 lightDir = normalize(u_LightPos - v_Pos);
	float diffuse = max(dot(normal, lightDir), 0.0);

	color = vec4(u_LightColor, 1) * u_AmbientFactor + texture(u_Texture, v_Texcoord);
	color = vec4(u_LightColor, 1) * (diffuse + u_AmbientFactor);
	color = vec4(normal, 1);
};