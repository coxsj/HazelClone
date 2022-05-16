#include <iostream>

#include "application.h"
namespace Hazel {
	Application::Application() {
		std::cout << "Welcome to HazelClone Game Engine\n";
	}
	
	void Application::run() {
		long long ctr{ 0 };
		while (true) {
			if (ctr++ > 10000000) {
				ctr = 0;
				std::cout << ".";
			}
		}
	}

}