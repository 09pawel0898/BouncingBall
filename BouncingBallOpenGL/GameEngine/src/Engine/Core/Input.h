#pragma once

#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"

#include "glm/vec2.hpp"

namespace En
{
	class Input
	{
	public:
		static glm::vec2 GetMousePosition(void);
		static bool IsKeyPressed(Keyboard::KeyCode key);
		static bool IsMouseButtonPressed(Mouse::MouseButtonCode button);
	};
}