#pragma once

#include "hzpch.h"

#include "Hazel/window.h"
#include "GLFW/glfw3.h"

namespace Hazel {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props) { init(props); }
		virtual ~WindowsWindow() { shutdown(); }

		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;
		bool WindowsWindow::isVSync() const override;
		void onUpdate() override;
		void setEventCallback(const EventCallbackFn& callback) override;
		void setVSync(bool enabled) override;
		
		virtual void* getNativeWindow() const override { return m_Window; }
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