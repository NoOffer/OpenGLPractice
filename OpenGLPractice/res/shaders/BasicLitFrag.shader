#version 330 core

out vec4 color;

in vec3 v_PosWS;
in vec3 v_Normal;
in vec2 v_Texcoord;

uniform sampler2D u_Texture;
uniform vec3 u_LightDir;
uniform vec3 u_LightColor;
uniform vec3 u_Ambient;
uniform vec3 u_CamPos;
uniform float u_Smoothness;

float LinearizeDepth(float depth)
{
	// 2 * far * near / far + near - (depth * 2 - 1) * (far - near)
	return (20.0 / (200 - depth * 199.8) - 0.1) / 99.9;
}

void main()
{
	float diffuse = dot(v_Normal, u_LightDir) * 0.5 + 0.5;
	vec3 h = normalize(u_CamPos - v_PosWS + u_LightDir);
	float specular = pow(dot(v_Normal, h), u_Smoothness) * u_Smoothness / 10;

	//color = vec4(u_LightColor, 1) * (diffuse + specular + material.ambient) * texture(u_Texture, v_Texcoord);
	color =	vec4(clamp(u_LightColor * (diffuse + specular) + u_Ambient, 0.0, 1.0), 1);
	//color = vec4(vec3(LinearizeDepth(gl_FragCoord.z)), 1.0);
};