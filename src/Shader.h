#pragma once

#include <iostream>
#include <unordered_map>

class ShaderProgram
{
private:
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocations;

	unsigned int GetUniformPosition(const std::string name);
public:
	ShaderProgram(const std::string vertFilepath, const std::string fragFilepath);
	~ShaderProgram();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform1i(const std::string name, int i1);
	void SetUniform4f(const std::string name, float f0, float f1, float f2, float f3);
};