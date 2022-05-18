#include "hzpch.h"
#include "windowsWindow.h"
#include "Hazel/log.h"

namespace Hazel {
	static bool s_GLFWInitialized = false;

	
	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}
	
	void WindowsWindow::init(const WindowProps& props) {
		m_Data.title = props.title;
		m_Data.width = props.width;
		m_Data.height = props.height;

		HZ_CORE_INFO("Creating window {0} ({1}, {2}", props.title, props.width, props.height);

		if (!s_GLFWInitialized) {
			//TODO glfwTerminate on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not initialize GLFW!");
			s_GLFWInitialized = true;
		}
		
		m_Window = glfwCreateWindow(static_cast<int>(props.width), static_cast<int>(props.height),
			m_Data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		setVSync(true);
	}
	void WindowsWindow::shutdown() {
		glfwDestroyWindow(m_Window);
	}
	void WindowsWindow::onUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	void WindowsWindow::setVSync(bool enabled) {
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}
}
