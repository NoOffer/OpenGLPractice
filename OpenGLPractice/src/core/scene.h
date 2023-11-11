#pragma once

#include "camera.h"
#include "directional_light.h"
#include "main_camera.h"
#include "model.h"
#include "skybox.h"

#include <vector>

class Scene
{
public:
	Scene(const char* name) { m_Name = name; }
	~Scene() {}

	// Light
	inline void SetDirectionalLight(const DirectionalLight& dirLight) { m_DirLight = dirLight; }
	inline void SetAmbient(vec3 ambient) { m_Ambient = ambient; }

	// Model
	void AddModel(
		const char* path,
		Shader* shaderRef,
		vec3 translation = vec3(0.0f),
		vec3 rotation = vec3(0.0f),
		vec3 scale = vec3(1.0f)
	);
	//void RemoveModel(const char* name);
	//Model* GetModel(const char* name);
	
	// Skybox
	void SetSkybox(
		const std::string& pos_x_path,
		const std::string& neg_x_path,
		const std::string& pos_y_path,
		const std::string& neg_y_path,
		const std::string& pos_z_path,
		const std::string& neg_z_path
	);

	void Render(bool renderSkybox = true);
	void Render(Camera cameram, bool renderSkybox = true);

private:
	const char* m_Name;
	DirectionalLight m_DirLight;
	vec3 m_Ambient;
	std::vector<Model> m_Models;
	Skybox m_Skybox;
};

