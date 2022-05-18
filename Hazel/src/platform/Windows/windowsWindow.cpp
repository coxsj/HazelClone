#include "hzpch.h"
#include "windowsWindow.h"
#include "Hazel/events/applicationEvent.h"
#include "Hazel/events/keyEvent.h"
#include "Hazel/events/mouseEvent.h"

namespace Hazel {
	//Global variables
	static bool s_GLFWInitialized = false;

	//Global functions
	static void GLFWErrorCallback(int error, const char* description) {
		HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props) {
		// Note this is the implementation of the base class Create method.
		// Each platform implements its own version of this.
		return new WindowsWindow(props);
	}
	
	unsigned int WindowsWindow::GetHeight() const { 
		return m_Data.height; 
	}
	unsigned int WindowsWindow::GetWidth() const { 
		return m_Data.width; 
	}
	void WindowsWindow::init(const WindowProps& props) {
		m_Data.title = props.title;
		m_Data.width = props.width;
		m_Data.height = props.height;

		HZ_CORE_INFO("Creating window {0}({1}, {2})", props.title, props.width, props.height);

		if (!s_GLFWInitialized) {
			//TODO glfwTerminate on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}
		//Create the window
		m_Window = glfwCreateWindow(static_cast<int>(props.width), static_cast<int>(props.height),
			m_Data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		// User pointer used in event callbacks
		glfwSetWindowUserPointer(m_Window, &m_Data);
		setVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			// When a window size event occurs on m_Window, GLFW runs this lambda function 
			// i.e GLFW executes this window resize event callback.
			// This routine creates a WindowResizeEvent event and then calls the event callback 
			// function which was registered in application.cpp using
			// m_Window->setEventCallback(BIND_EVENT_FN(onEvent));
			// In all of this, the event parameter (a ref) gets passed along.
			// The application's onEvent method dispatches the event.
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;
			// Create the corresponding Hazel event
			WindowResizeEvent event(width, height);
			data.eventCallback(event);
		});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.eventCallback(event);
		});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			//TODO convert GLFW keycode to HAZEL keycode i.e. graphics library independent
			switch (action) {
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					// TODO- '1' is placeholder. Extract actual repeat count from GLFW
					int placeholder = 1;
					KeyPressedEvent event(key, placeholder);
					data.eventCallback(event);
					break;
				}
				default:
					HZ_ASSERT(true, "Unexpected key event");
					break;
			}
		});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.eventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.eventCallback(event);
				break;
			}
			default:
				HZ_ASSERT(true, "Unexpected mouse button event");
				break;
			}
		});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
			data.eventCallback(event);
		});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
			data.eventCallback(event);
			});
	}
	bool WindowsWindow::isVSync() const {
		return m_Data.VSync; 
	}
	void WindowsWindow::onUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	void WindowsWindow::setEventCallback(const EventCallbackFn& callback)  {
		m_Data.eventCallback = callback;
	}
	void WindowsWindow::setVSync(bool enabled) {
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}
	void WindowsWindow::shutdown() {
		glfwDestroyWindow(m_Window);
	}
	
}
