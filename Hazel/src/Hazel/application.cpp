
#include "hzpch.h"

#include "Hazel/application.h"
#include "glad/glad.h"
#include "Hazel/input.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_instance = nullptr;

	Application::Application() : m_Running(true) {
		HZ_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->setEventCallback(BIND_EVENT_FN(onEvent));
		m_ImGuiLayer = new  ImguiLayer;
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_vertexArray);
		glBindVertexArray(m_vertexArray);

		glGenBuffers(1, &m_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		std::cout << "Welcome to HazelClone Game Engine\n";
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher  dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
		
		HZ_CORE_TRACE("Application::OnEvent {0}", e);

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
	void Application::PushOverlay(Layer* layer) {
		m_layerStack.PushOverlay(layer);
	}
	void Application::run() {

		while (m_Running) {
			glClearColor(0.1f, 0.15f, 0.15f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_vertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_layerStack)
				layer->onUpdate(); //this is where we submit things for rendering

			//This bock will run on the render thread
			m_ImGuiLayer->begin();
			for (Layer* layer : m_layerStack)
				layer->onImGuiRender();
			m_ImGuiLayer->end();

			//Print mouse pos to log
			//auto [x, y] = Input::getMousePosition();
			//HZ_CORE_TRACE("{0}, {1}", x, y);

			m_Window->onUpdate();
		}
		// Where is GLFWTerminate?
	}

	
}