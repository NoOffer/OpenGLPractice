#include "scene.h"

void Scene::AddModel(
	const char* path,
	Shader* shaderRef,
	vec3 translation,
	vec3 rotation,
	vec3 scale
)
{
	Model model(path, shaderRef);
	model.SetPosition(translation);
	model.SetRotation(rotation);
	model.SetScale(scale);
	m_Models.push_back(std::move(model));
}

void Scene::SetSkybox(
	const std::string& pos_x_path,
	const std::string& neg_x_path,
	const std::string& pos_y_path,
	const std::string& neg_y_path,
	const std::string& pos_z_path,
	const std::string& neg_z_path
)
{
	m_Skybox.SetCubeMap(
		pos_x_path, neg_x_path,
		pos_y_path, neg_y_path,
		pos_z_path, neg_z_path
	);
}

void Scene::Render(bool renderSkybox)
{
	mat4 viewMatrix = MainCamera::GetViewMatrix();
	mat4 projMatrix = MainCamera::GetProjMatrix();

	for (std::vector<Model>::iterator itr = m_Models.begin(); itr != m_Models.end(); itr++)
	{
		Shader* shaderRef = (*itr).GetShaderRef();
		if (shaderRef)
		{
			// Transformation matrix
			(*shaderRef).SetUniformMat4f("u_Matrix_VP", mul(projMatrix, viewMatrix));
			(*shaderRef).SetUniformMat4f("u_Matrix_M", (*itr).GetModelMatrix());
			(*shaderRef).SetUniformMat3f("u_Matrix_M_Normal", mat3((*itr).GetNormalMatrix()));

			// Light info
			(*shaderRef).SetUniform3f("u_LightDir", m_DirLight.direction);
			(*shaderRef).SetUniform3f("u_LightColor", m_DirLight.color);
			(*shaderRef).SetUniform3f("u_Ambient", m_Ambient);

			// Cam info
			(*shaderRef).SetUniform3f("u_CamPos", MainCamera::GetPosition());

			// Material properties
			(*shaderRef).SetUniform1f("u_Smoothness", 5.0f);
		}

		(*itr).Render();
	}

	if (renderSkybox)
	{
		m_Skybox.Render(projMatrix, viewMatrix);
	}
}
