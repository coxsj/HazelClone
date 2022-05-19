#pragma once

#include "Hazel/layer.h"
#include "imgui.h"
#include "platform/OpenGL/imguiOpenGLRenderer.h"

namespace Hazel {

	class HAZEL_API ImguiLayer : public Layer {
	public:
		ImguiLayer();
		~ImguiLayer();

		virtual void onAttach();
		virtual void onDetach();
		virtual void onUpdate();
		virtual void onEvent(Event& event);

	private:
		float m_time = 0.0f;
	};

}
