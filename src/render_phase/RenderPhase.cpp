#include "RenderPhase.h"

namespace phase
{
	PhaseMenu::PhaseMenu(RenderPhase*& current)
		: m_CurrentPhase(current)
	{
	}

	void PhaseMenu::OnGUIRender()
	{
		for (std::pair<std::string, std::function<RenderPhase* ()>>& phase : m_Phases) {
			if (ImGui::Button(phase.first.c_str())) {
				m_CurrentPhase = phase.second();
			}
		}
	}
}