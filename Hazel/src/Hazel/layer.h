#pragma once

#include "Hazel/core.h"
#include "Hazel/events/event.h"

namespace Hazel {

	class HAZEL_API Layer 	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach(){}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getName() const { return m_debugName; }

	protected:
		std::string m_debugName;
	};

}