#pragma once

#include "hzpch.h"
#include "event.h"
namespace Hazel {

	class HAZEL_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(kWindowResize)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(kWindowClose)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	};

	class HAZEL_API AppTickEvent : public Event {
		AppTickEvent(){}

		EVENT_CLASS_TYPE(kAppTick)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	};

	class HAZEL_API AppUpdateEvent : public Event {
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(kAppUpdate)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	};

	class HAZEL_API AppRenderEvent : public Event {
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(kAppRender)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	};
}