#pragma once

#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	~Window();
	bool Init(int width, int height);
	bool Alive();
	void Update();

private:
	GLFWwindow* m_Window;
};