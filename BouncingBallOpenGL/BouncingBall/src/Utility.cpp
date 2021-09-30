#include "Utility.h"

template <> bool IsButtonCovered<ButtonType::Round>(const En::Sprite& button, unsigned radius)
{
	glm::vec2 mousePos = En::Input::GetMousePosition();
	glm::vec2 buttonPos = button.GetPosition();

	glm::vec2 vec = { abs(buttonPos.x - mousePos.x),
						abs(buttonPos.y - mousePos.y) };

	return (sqrt(vec.x * vec.x + vec.y * vec.y) > radius) ?
		false : true;
}

template <> bool IsButtonCovered<ButtonType::Rectangular>(const En::Sprite& button, unsigned ununsed)
{
	glm::vec2 mousePos = En::Input::GetMousePosition();
	glm::vec2 buttonPos = button.GetPosition();

	return (mousePos.y > buttonPos.y && mousePos.y < buttonPos.y + button.GetSize().y) ?
		true : false;
}