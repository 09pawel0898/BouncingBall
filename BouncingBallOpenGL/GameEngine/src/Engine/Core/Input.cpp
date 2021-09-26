#include "Input.h"
#include "Application.h"

namespace En
{

	bool Input::IsKeyPressed(Keyboard::KeyCode key)
	{
		auto window = static_cast<GLFWwindow*>(Application::m_Instance->GetWindow()->GetWindowHandle());
		int state = glfwGetKey(window, (int16_t)key);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(Mouse::MouseButtonCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::m_Instance->GetWindow()->GetWindowHandle());
		auto state = glfwGetMouseButton(window, (int16_t)button);
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition(void)
	{
		auto window = static_cast<GLFWwindow*>(Application::m_Instance->GetWindow()->GetWindowHandle());
		double xPos, yPos;
		glfwGetCursorPos(window, 
						 &xPos, 
						 &yPos);

		return {(float)xPos,(float)yPos};
	}

}