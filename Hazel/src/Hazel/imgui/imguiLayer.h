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
		ImguiLayer(){}
		~ImguiLayer(){}

		virtual void onAttach();
		virtual void onDetach();
		virtual void onUpdate();
		virtual void onEvent(Event& event);

	private:
		float m_time = 0.0f;

		private:
			bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
			bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
			bool OnMouseMovedEvent(MouseMovedEvent& e);
			bool OnMouseScrolledEvent(MouseScrolledEvent& e);
			bool OnKeyPressedEvent(KeyPressedEvent& e);
			bool OnKeyReleasedEvent(KeyReleasedEvent& e);
			bool OnKeyTypedEvent(KeyTypedEvent& e);
			bool OnWindowResizeEvent(WindowResizeEvent& e);
	};

}
