
#include "hzpch.h"

#include "Hazel/application.h"
#include "Hazel/events/applicationEvent.h"
#include "Hazel/log.h"
#include "Hazel/window.h"
#include "GLFW/glfw3.h"

namespace Hazel {
	Application::Application() {
		std::cout << "Welcome to HazelClone Game Engine\n";
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	
	void Application::run() {
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(kEventCategoryApplication)) HZ_CORE_TRACE(e);

		while (m_Running) {
			HZ_CORE_TRACE(e);
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->onUpdate();
		}
		if (e.IsInCategory(kEventCategoryInput)) HZ_CORE_TRACE(e);


		long long ctr{ 0 };
		while (true) {
			if (ctr++ > 100000000) {
				ctr = 0;
				std::cout << ".";
			}
		}
	}

}