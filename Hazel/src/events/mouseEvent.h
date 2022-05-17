#pragma once

#include <sstream>

#include "event.h"
namespace Hazel {

	class HAZEL_API MouseMovedEvent : public Event {
		MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

		public:
		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();

		}
		EVENT_CLASS_TYPE(kMouseMoved)
		EVENT_CLASS_CATEGORY(kEventCategoryMouse | kEventCategoryInput)
	protected:
		float m_MouseX, m_MouseY;
	};

	class HAZEL_API MouseScrolledEvent : public Event {
		MouseScrolledEvent(float xOffset, float yOffset) 
			: m_XOffset(xOffset), m_YOffset(m_YOffset) {}

	public:
		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }


		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}
		EVENT_CLASS_TYPE(kMouseScrolled)
		EVENT_CLASS_CATEGORY(kEventCategoryMouse | kEventCategoryInput)
	protected:
		float m_XOffset, m_YOffset;
	};

	class HAZEL_API MouseButtonEvent : public Event {
	public:
		inline float GetMouseButton() const { return m_Button; }
		EVENT_CLASS_CATEGORY(kEventCategoryMouse | kEventCategoryInput)
	protected:
		MouseButtonEvent(int button) : m_Button(button) {}
		int m_Button;
	};

	class HAZEL_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button) 
			: MouseButtonEvent(button) {}
		
		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(kMouseButtonPressed)
	};

	class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(kMouseButtonReleased)
	};
}