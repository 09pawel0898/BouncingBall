#pragma once

#include <Engine.h>

namespace En
{
	class Sprite;
}

enum class ButtonType : uint8_t
{
	Round, Rectangular
};

struct RectangleShape
{
	glm::vec2 pos;
	glm::vec2 size;
	
	RectangleShape(const glm::vec2& _pos, const glm::vec2& _size)
		:	pos(_pos), size(_size)
	{}

	glm::vec2 GetPosition(void) const { return pos; }
};

template <ButtonType T>
bool IsButtonCovered(const En::Sprite&, unsigned = 0){
	static_assert(false);
}

template <> bool IsButtonCovered<ButtonType::Round>(const En::Sprite& button, unsigned radius);
template <> bool IsButtonCovered<ButtonType::Rectangular>(const En::Sprite& button, unsigned ununsed);