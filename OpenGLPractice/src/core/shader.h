#pragma once

#include <unordered_map>
#include <string>

#include "glm/glm.hpp"

class Shader
{
private:
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocations;

	unsigned int GetUniformPosition(const std::string name);
public:
	Shader();
	Shader(const std::string vertFilepath, const std::string fragFilepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform1i(const std::string name, int i);
	void SetUniform1f(const std::string name, float f);
	void SetUniform3f(const std::string name, const glm::vec3& v);
	void SetUniform4f(const std::string name, float f0, float f1, float f2, float f3);
	void SetUniformMat3f(const std::string name, const glm::mat3& matrix);
	void SetUniformMat4f(const std::string name, const glm::mat4& matrix);
};