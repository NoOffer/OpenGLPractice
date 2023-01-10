#include "GUI.h"

void GUI::Init(GLFWwindow* window, const char* version, bool darkmode)
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(version);
	if (darkmode) {
		ImGui::StyleColorsDark();
	}
}

void GUI::NewFrame()
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GUI::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::CleanUp()
{
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}