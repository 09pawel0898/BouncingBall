#pragma once

#include "Event.h"

namespace Engine
{
	namespace Mouse
	{
		enum class MouseCode : uint16_t
		{
			Button0 = 0,
			Button1 = 1,
			Button2 = 2,
			Button3 = 3,
			Button4 = 4,
			Button5 = 5,
			ButtonLeft = Button0,
			ButtonRight = Button1
		};

		class MouseMovedEvent : public Event
		{
		private:
			float m_MouseX, m_MouseY;

		public:
			MouseMovedEvent(float x, float y)
				:	m_MouseX(x),
					m_MouseY(y)
			{}

			inline float GetX(void) const { return m_MouseX; }
			inline float GetY(void) const { return m_MouseY; }

			EVENT_CLASS_TYPE(MouseMoved)
		};

		class MouseButtonEvent : public Event
		{
		protected:
			MouseCode m_ButtonCode;

			MouseButtonEvent(MouseCode button) 
				:	m_ButtonCode(button)
			{}
		public:
			inline MouseCode getButtonCode(void) const 
			{ return m_ButtonCode; }
		};

		class MouseButtonPressedEvent : public MouseButtonEvent
		{
		public:
			MouseButtonPressedEvent(MouseCode button) 
				:	MouseButtonEvent(button)
			{}

			EVENT_CLASS_TYPE(MouseButtonPressed)
		};

		class MouseButtonReleasedEvent : public MouseButtonEvent
		{
		public:
			MouseButtonReleasedEvent(MouseCode button) 
				:	MouseButtonEvent(button)
			{}

			EVENT_CLASS_TYPE(MouseButtonReleased)
		};
	}
}