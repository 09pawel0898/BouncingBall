#pragma once

#include "Event.h"

namespace En
{
	namespace Keyboard
	{
		enum class KeyCode : uint16_t
		{
			W = 87,
			A = 65,
			S = 83,
			D = 68,
		};

		class KeyEvent : public Event
		{
		protected:
			KeyCode m_KeyCode;

			KeyEvent(KeyCode keyCode) 
				:	m_KeyCode(keyCode)
			{}
		public:
			inline KeyCode GetKeyCode(void) const
			{	return m_KeyCode;	}
		};
		
		class KeyPressedEvent : public KeyEvent
		{
		public:
			KeyPressedEvent(KeyCode keyCode) 
				:	KeyEvent(keyCode)
			{}

			EVENT_CLASS_TYPE(KeyPressed)
		};

		class KeyReleasedEvent : public KeyEvent
		{
		public:
			KeyReleasedEvent(KeyCode keyCode) 
				:	KeyEvent(keyCode)
			{}

			EVENT_CLASS_TYPE(KeyReleased)
		};

	}
}