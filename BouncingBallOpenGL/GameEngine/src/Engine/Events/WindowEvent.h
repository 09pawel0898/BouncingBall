#pragma once

#include "Event.h"

namespace Engine
{
	class WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent() = default;
		EVENT_CLASS_TYPE(WindowClosed);
	};
}