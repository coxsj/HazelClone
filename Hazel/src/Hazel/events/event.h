#pragma once

#include "hzpch.h"

#include "core.h"

namespace Hazel {
	// Events are currently blocking
	// Future: buffer events and process events during update phase.

	enum class EventType {
		kNone = 0,
		kWindowClose, kWindowResize, kWindowFocus, kWindowLostFocus, kWindowMoved,
		kAppTick, kAppUpdate, kAppRender,
		kKeyPressed, kKeyReleased,
		kMouseButtonPressed, kMouseButtonReleased, kMouseMoved, kMouseScrolled
	};
	// Categories enable (fast & efficient) filtering of events
	enum EventCategory {
		kNone = 0,
		kEventCategoryApplication = BIT(0),
		kEventCategoryInput       = BIT(1),
		kEventCategoryKeyboard    = BIT(2),
		kEventCategoryMouse       = BIT(3),
		kEventCategoryMouseButton = BIT(4),
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type; }\
								virtual EventType GetEventType() const override {return GetStaticType();}\
								virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}
	// Event Class - Base class for events
	class HAZEL_API Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0; // Likely should be debug only
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
	protected:
		bool m_handled = false;
	};

	class EventDispatcher {
		
	public:
		EventDispatcher(Event& event) :m_Event(event){}

		template<typename T, typename F>
		bool Dispatch(const F& func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}