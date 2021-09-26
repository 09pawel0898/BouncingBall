#pragma once

#include <functional>

namespace En
{
	enum class EventType
	{
		None = 0,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved,
		WindowClosed
	};

#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType(void) { return EventType::type; }\
								virtual EventType GetEventType(void) const override { return GetStaticType(); }

	class Event
	{
	protected:
		bool m_Handled;
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual ~Event() = default;
	};

	class EventDispatcher
	{
		template<typename EventType>
		using EventFunction = std::function<bool(EventType&)>;
	private:
		Event& m_Event;
	public:
		EventDispatcher(Event& event)
			:	m_Event(event)
		{}

		template<typename EventType>
		bool Dipatch(const EventFunction<EventType>& func)
		{
			if (m_Event.GetEventType() == EventType::GetStaticType())
			{
				m_Event.m_Handled = func(*static_cast<EventType*>(&m_Event));
				return true;
			}
			return false;
		}
	};
}