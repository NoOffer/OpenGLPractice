#pragma once

#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

template<typename type>
struct GUIVariable
{

	type value;
};

class GUI
{
public:
	static void Init(GLFWwindow* window, const char* version, bool darkmode = true);
	static void NewFrame();
	static void Render();
	static void CleanUp();
};
