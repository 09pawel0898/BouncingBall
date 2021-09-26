#pragma once

#include "Event.h"

namespace En
{
	namespace Mouse
	{
		enum class MouseButtonCode : uint16_t
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
			double m_MouseX, m_MouseY;

		public:
			MouseMovedEvent(double x, double y)
				:	m_MouseX(x),
					m_MouseY(y)
			{}

			inline double GetX(void) const { return m_MouseX; }
			inline double GetY(void) const { return m_MouseY; }

			EVENT_CLASS_TYPE(MouseMoved)
		};

		class MouseButtonEvent : public Event
		{
		protected:
			MouseButtonCode m_ButtonCode;

			MouseButtonEvent(MouseButtonCode button) 
				:	m_ButtonCode(button)
			{}
		public:
			inline MouseButtonCode getButtonCode(void) const 
			{ return m_ButtonCode; }
		};

		class MouseButtonPressedEvent : public MouseButtonEvent
		{
		public:
			MouseButtonPressedEvent(MouseButtonCode button) 
				:	MouseButtonEvent(button)
			{}

			EVENT_CLASS_TYPE(MouseButtonPressed)
		};

		class MouseButtonReleasedEvent : public MouseButtonEvent
		{
		public:
			MouseButtonReleasedEvent(MouseButtonCode button) 
				:	MouseButtonEvent(button)
			{}

			EVENT_CLASS_TYPE(MouseButtonReleased)
		};
	}
}