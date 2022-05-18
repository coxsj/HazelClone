#pragma once
#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::createApplication();

int main(int argc, char** argv) {
	Hazel::Log::init();
	HZ_CORE_WARN("Initialized Core Log!");
	HZ_CLIENT_INFO("Initialized Client Log!");

	auto app = Hazel::createApplication();
	app->run();
	delete app;
}
#endif