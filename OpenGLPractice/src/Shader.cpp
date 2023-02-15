#include "Shader.h"

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "glm/gtc/type_ptr.hpp"

//static void ParseShader(std::string& filepath)
//{
//	std::ifstream stream(filepath);
//
//	enum class ShaderType
//	{
//		NONE = -1, VERTEX = 0, FRAGMENT = 1
//	};
//
//	std::string line;
//	std::stringstream ss[2];
//	ShaderType shaderType = ShaderType::NONE;
//	while (getline(stream, line)) {
//		if (line.find("#shader") != std::string::npos) {
//			if (line.find("vertex") != std::string::npos) {
//				shaderType = ShaderType::VERTEX;
//			}
//			else if (line.find("fragment") != std::string::npos) {
//				shaderType = ShaderType::FRAGMENT;
//			}
//		}
//		else {
//			ss[(int)shaderType] << line << '\n';
//		}
//	}
//
//	stream.close();
//}

static std::string ReadShader(std::string filepath)
{
	std::ifstream fileStream(filepath);
	if (!fileStream.is_open()) {
		std::cout << "Failed to load shader at " << filepath << std::endl;
		return "";
	}
	std::stringstream ss;
	ss << fileStream.rdbuf();
	fileStream.close();

	return ss.str();
}

static unsigned int ComplieShader(const std::string& source, unsigned int type)
{
	// Create a shader object
	unsigned int shaderId = glCreateShader(type);
	// Pass in the shader code
	const char* src = source.c_str();
	glShaderSource(shaderId, 1, &src, nullptr);
	// Compile
	glCompileShader(shaderId);

	// Error handling
	int status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		// Retrieve the length of the error message
		int msgLength;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &msgLength);
		// Message string
		char* msg = (char*)malloc(msgLength * sizeof(char));
		glGetShaderInfoLog(shaderId, msgLength, &msgLength, msg);
		std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "Shader Compilation Failure: "
			<< msg << std::endl;
		// Free the space for the message string
		free(msg);

		// Delete the unsuccessfully compiled shader
		glDeleteShader(shaderId);

		return 0;
	}

	return shaderId;
}

static int CreateShaderProgram(const std::string vertFilepath, const std::string fragFilepath)
{
	// Create a program object that holds the shaders
	unsigned int programId = glCreateProgram();
	// Get the references of the shaders after compilation
	unsigned int vs = ComplieShader(ReadShader(vertFilepath), GL_VERTEX_SHADER);
	unsigned int fs = ComplieShader(ReadShader(fragFilepath), GL_FRAGMENT_SHADER);

	// Attach the shaders and activate the program
	glAttachShader(programId, vs);
	glAttachShader(programId, fs);
	glLinkProgram(programId);
	glValidateProgram(programId);

	// Destroy the shaders since they have been linked to the program
	glDeleteShader(vs);
	glDeleteShader(fs);

	return programId;
}

Shader::Shader()
{
	m_RendererID = 0;
}

Shader::Shader(const std::string vertFilepath, const std::string fragFilepath)
{
	m_RendererID = CreateShaderProgram(vertFilepath, fragFilepath);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

unsigned int Shader::GetUniformPosition(const std::string name)
{
	if (m_UniformLocations.find(name) != m_UniformLocations.end()) {
		return m_UniformLocations[name];
	}

	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1) { 
		std::cout << "[Warning] Uniform " << name << " does not exist." << std::endl;
	}
	m_UniformLocations[name] = location;
	return location;
}

void Shader::SetUniform1i(const std::string name, int i)
{
	Bind();
	glUniform1i(GetUniformPosition(name), i);
}

void Shader::SetUniform1f(const std::string name, float f)
{
	Bind();
	glUniform1f(GetUniformPosition(name), f);
}

void Shader::SetUniform3f(const std::string name, const glm::vec3& v)
{
	Bind();
	glUniform3f(GetUniformPosition(name), v.x, v.y, v.z);
}

void Shader::SetUniform4f(const std::string name, float f0, float f1, float f2, float f3)
{
	Bind();
	glUniform4f(GetUniformPosition(name), f0, f1, f2, f3);
}

void Shader::SetUniformMat4f(const std::string name, const glm::mat4& matrix)
{
	Bind();
	glUniformMatrix4fv(GetUniformPosition(name), 1, GL_FALSE, glm::value_ptr(matrix));
}