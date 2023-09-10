#version 330 core

struct Material
{
	float smoothness;
	float ambient;
};

out vec4 color;

in vec3 v_PosWS;
in vec3 v_Normal;
in vec2 v_Texcoord;

uniform sampler2D u_Texture;
uniform vec3 u_LightPos;
uniform vec3 u_LightColor;
uniform vec3 u_CamPos;
uniform Material material;

float LinearizeDepth(float depth)
{
	// 2 * far * near / far + near - (depth * 2 - 1) * (far - near)
	return (20.0 / (200 - depth * 199.8) - 0.1) / 99.9;
}

void main()
{
	vec3 lightDir = normalize(u_LightPos - v_PosWS);
	float diffuse = dot(v_Normal, lightDir) * 0.5 + 0.5;
	vec3 h = normalize(u_CamPos - v_PosWS + lightDir);
	float specular = pow(clamp(dot(v_Normal, h), 0.0, 1.0), material.smoothness);

	//color = vec4(u_LightColor, 1) * (diffuse + specular + material.ambient) * texture(u_Texture, v_Texcoord);
	color = vec4(u_LightColor * (diffuse + specular + material.ambient), 1);
	//color = vec4(vec3(LinearizeDepth(gl_FragCoord.z)), 1.0);
};