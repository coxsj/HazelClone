#pragma once

#include "Hazel/core.h"
#include "Hazel/window.h"
#include "Hazel/events/applicationEvent.h"

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application() {}

		void run();
		void onEvent(Event& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent& e);
	};


	//To be defined in client
	Application* createApplication();
}

