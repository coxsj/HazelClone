#pragma once

#include "Hazel/layer.h"
//#include "imgui.h"
//#include "platform/OpenGL/imguiOpenGLRenderer.h"
#include "Hazel/events/applicationEvent.h"
#include "Hazel/events/keyEvent.h"
#include "Hazel/events/mouseEvent.h"

namespace Hazel {

	class HAZEL_API ImguiLayer : public Layer {
	public:
		ImguiLayer() : Layer("ImGuiLayer") {}
		~ImguiLayer(){}

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiRender() override;

		void begin();
		void end();

	private:
		float m_time = 0.0f;
	};

}
