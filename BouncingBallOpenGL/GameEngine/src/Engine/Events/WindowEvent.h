#pragma once

#include "Event.h"

namespace En
{
	class WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent() = default;
		EVENT_CLASS_TYPE(WindowClosed);
	};
}