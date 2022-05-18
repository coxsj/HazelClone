
#include "hzpch.h"

#include "Hazel/application.h"
#include "GLFW/glfw3.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() : m_Running(true) {
		std::cout << "Welcome to HazelClone Game Engine\n";
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->setEventCallback(BIND_EVENT_FN(onEvent));
	}
	void Application::onEvent(Event& e)
	{
		EventDispatcher  dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
		
		HZ_CORE_TRACE("{0}", e);

		for (auto it = m_layerStack.end(); it != m_layerStack.begin(); ) {
			(*--it)->onEvent(e);
			if (e.handled) break;
		}
	}
	bool Application::onWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
	void Application::PushLayer(Layer* layer) {
		m_layerStack.PushLayer(layer);
	}
	void Application::PushOverlay(Layer* overlay) {
		m_layerStack.PushOverlay(overlay);
	}
	void Application::run() {

		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_layerStack)
				layer->onUpdate();

			m_Window->onUpdate();
		}
		// Where is GLFWTerminate?
	}

	
}