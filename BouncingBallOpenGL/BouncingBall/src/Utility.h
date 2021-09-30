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

template <ButtonType T>
bool IsButtonCovered(const En::Sprite&, unsigned = 0){
	static_assert(false);
}

template <> bool IsButtonCovered<ButtonType::Round>(const En::Sprite& button, unsigned radius);
template <> bool IsButtonCovered<ButtonType::Rectangular>(const En::Sprite& button, unsigned ununsed);