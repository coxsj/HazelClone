#pragma once

#include "hzpch.h"

#include "Hazel/window.h"
#include "GLFW/glfw3.h"

namespace Hazel {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props) { init(props); }
		virtual ~WindowsWindow() { shutdown(); }

		void onUpdate() override;
		unsigned int GetWidth() const override { return m_Data.width; }
		unsigned int GetHeight() const override { return m_Data.height; }

		// Window Attributes
		void setEventCallback(const EventCallbackFn& callback) override { 
			m_Data.eventCallback = callback; 
		}
		void setVSync(bool enabled) override;
		bool WindowsWindow::isVSync() const override{ return m_Data.VSync; }
	private:
		virtual void init(const WindowProps& props);
		virtual void shutdown();

	private:
		GLFWwindow* m_Window;

		// This struct will be used to pass data to GLFW during Window events
		struct WindowData {
			std::string title;
			unsigned int width;
			unsigned int height;
			bool VSync;

			EventCallbackFn eventCallback;
		};

		WindowData m_Data;
	};
}