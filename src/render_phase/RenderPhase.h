#pragma once

#include <vector>
#include <string>
#include <functional>

#include "imgui/imgui.h"

namespace phase
{
	class RenderPhase
	{
	public:
		RenderPhase() {}
		~RenderPhase() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnGUIRender() {}
	};

	class PhaseMenu : public RenderPhase
	{
	private:
		std::vector<std::pair<std::string, std::function<RenderPhase* ()>>> m_Phases;
		RenderPhase*& m_CurrentPhase;
	public:
		PhaseMenu(RenderPhase*& current);

		void OnGUIRender() override;

		template<typename T>
		void RegisterPhase(std::string phaseName)
		{
			m_Phases.push_back(std::make_pair(phaseName, []() { return new T(); }));
		}
	};
}
