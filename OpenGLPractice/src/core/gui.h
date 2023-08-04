#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class GUI
{
public:
	static void Init(GLFWwindow* window, const char* version, bool darkmode = true);
	static void NewFrame();
	static void Render();
	static void Shutdown();
};

