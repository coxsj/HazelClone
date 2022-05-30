#pragma once

#include "Hazel/core.h"
#include "Hazel/window.h"
#include "Hazel/layerStack.h"
#include "Hazel/events/event.h"
#include "Hazel/events/applicationEvent.h"

#include "Hazel/imgui/imguiLayer.h"

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application() {}

		void run();
		void onEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		
		Window& getWindow() { return *m_Window; }
		
		static Application& Get() { return *s_instance; }
		
		unsigned int m_vertexArray, m_vertexBuffer, m_indexBuffer;
		
	private:
		std::unique_ptr<Window> m_Window;
		ImguiLayer* m_ImGuiLayer;
		bool m_Running;
		LayerStack m_layerStack;
		static Application* s_instance;

		bool onWindowClose(WindowCloseEvent& e);
	};

	//To be defined in client
	Application* createApplication();
}

