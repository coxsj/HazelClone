#pragma once

#include "hzpch.h"

#include "Hazel/core.h"
#include "Hazel/events/event.h"

namespace Hazel {

	struct WindowProps {
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string& t = "Hazel Engine", unsigned int w=1280, unsigned int h= 720)
			:title(t), width(w), height(h) {}
	};

	// Interface representing a desktop system window
	// This has to be implemented per platform
	class HAZEL_API Window{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window(){}

		virtual void onUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window Attributes
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		//Implementing class can return any kind of window since we specify void*
		virtual void* getNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}