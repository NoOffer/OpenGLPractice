#pragma once

#include <GLAD/glad.h>
#include <iostream>

//#define LogInfo(x) std::cout << (x) << std::endl

// ------------------------------------------------------------------------------------------------------------ Custom Helper Methods
static void LogInfo(const char* msg) { std::cout << msg << std::endl; }

static void LogWarning(const char* msg) { std::cout << "[Warning] " << msg << std::endl; }

static void LogError(const char* err)
{
	std::cout << "[Error] " << err << std::endl;
	__debugbreak();
}

static bool LogOpenGLError(const char* extraMsg = NULL)
{
	GLenum e = glGetError();
	if (e)
	{
		if (extraMsg) std::cout << extraMsg << std::endl;
		while (e)
		{
			std::cout << "[OpenGL Error] (" << e << ")" << std::endl;
			e = glGetError();
		}
		__debugbreak();
		return false;
	}
	return true;
}
