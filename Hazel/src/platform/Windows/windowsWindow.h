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

		inline unsigned int GetWidth() const override { return m_Data.width; }
		inline unsigned int GetHeight() const override { return m_Data.height; }

		// Window Attributes
		inline void setEventCallback(const EventCallbackFn& callback) override { 
			m_Data.EventCallback = callback; 
		}
		void setVSync(bool enabled) override;
		bool WindowsWindow::isVSync() const override{ return m_Data.VSync; }
	private:
		virtual void init(const WindowProps& props);
		virtual void shutdown();

	private:
		GLFWwindow* m_Window;

		struct WindowData {
			std::string title;
			unsigned int width;
			unsigned int height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}