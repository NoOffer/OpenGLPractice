#pragma once

#include "RenderPhase.h"

namespace phase
{
	class ClearPhase : public RenderPhase
	{
	private:
		float m_ClearColor[4];
	public:
		ClearPhase();

		void OnRender() override;
		void OnGUIRender() override;
	};
}
