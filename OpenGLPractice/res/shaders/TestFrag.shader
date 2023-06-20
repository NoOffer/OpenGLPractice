#version 330 core

struct Material
{
	float smoothness;
	float ambient;
};

layout(location = 0) out vec4 color;

in vec3 v_PosWS;
in vec3 v_Normal;
in vec2 v_Texcoord;

uniform sampler2D u_Texture;
uniform vec3 u_LightPos;
uniform vec3 u_LightColor;
uniform vec3 u_CamPos;
uniform Material material;

void main()
{
	vec3 lightDir = normalize(u_LightPos - v_PosWS);
	float diffuse = max(dot(v_Normal, lightDir), 0.0);
	vec3 h = normalize(u_CamPos - v_PosWS + lightDir);
	float specular = pow(max(dot(v_Normal, h), 0.0), material.smoothness);

	float h_factor = step(0.01 * length(cross(v_Normal, vec3(0, 1, 0))), mod(v_PosWS.y, 0.1));

	//color = vec4(u_LightColor, 1) * (diffuse + specular + material.ambient) * texture(u_Texture, v_Texcoord);
	color = vec4(h_factor, h_factor, h_factor, 1);
	//color = vec4(u_LightColor * (diffuse + specular + material.ambient), 1);
	//color = vec4(1, 1, 1, 1);
};