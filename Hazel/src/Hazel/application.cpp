#include <iostream>

#include "application.h"
#include "events/applicationEvent.h"
#include "log.h"

namespace Hazel {
	Application::Application() {
		std::cout << "Welcome to HazelClone Game Engine\n";
	}
	
	void Application::run() {
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(kEventCategoryApplication)) HZ_CORE_TRACE(e);
		if (e.IsInCategory(kEventCategoryInput)) HZ_CORE_TRACE(e);

		long long ctr{ 0 };
		while (true) {
			if (ctr++ > 100000000) {
				ctr = 0;
				std::cout << ".";
				std::cout << ".";


















			}
		}
	}

}