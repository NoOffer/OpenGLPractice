#include "ClearPhase.h"

#include <GL/glew.h>

namespace phase
{
	ClearPhase::ClearPhase()
		: m_ClearColor { 0.11f, 0.11f, 0.12f, 1.0f }
	{
	}

	void ClearPhase::OnRender()
	{
		glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void ClearPhase::OnGUIRender()
	{
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}

}