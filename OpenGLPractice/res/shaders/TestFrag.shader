#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_PosWS;
in vec3 v_Normal;
in vec2 v_Texcoord;

uniform sampler2D u_Texture;
uniform vec3 u_LightPos;
uniform vec3 u_LightColor;
uniform vec3 u_CamPos;
uniform float u_AmbientFactor;

void main()
{
	vec3 lightDir = normalize(u_LightPos - v_PosWS);
	float diffuse = max(dot(v_Normal, lightDir), 0.0);
	vec3 h = normalize(u_CamPos - v_PosWS + lightDir);
	float specular = pow(max(dot(v_Normal, h), 0.0), 32);

	color = vec4(u_LightColor, 1) * (diffuse + specular + u_AmbientFactor) * texture(u_Texture, v_Texcoord);
	// color = vec4(specular, specular, specular, 1);
};