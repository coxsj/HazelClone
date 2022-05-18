#pragma once

#include "Hazel/core.h"
#include "Hazel/window.h"
#include "Hazel/layerStack.h"
#include "Hazel/events/event.h"
#include "Hazel/events/applicationEvent.h"

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application() {}

		void run();
		void onEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running;
		LayerStack m_layerStack;

		bool onWindowClose(WindowCloseEvent& e);
	};

	//To be defined in client
	Application* createApplication();
}

