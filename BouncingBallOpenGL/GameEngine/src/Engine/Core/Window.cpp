#include "Window.h"

#include "../Events/WindowEvent.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"

namespace En
{
	static void GLFWErrorCallback(int error, const char* description)
	{
		std::cerr << "GLFW error ocurred [ " << description << " ]\n";
	}

	Window::Window(const WindowProperties& props)
	{
		InitProperties(props);

		EN_ASSERT(glfwInit());

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, 0);

		m_WindowHandle = glfwCreateWindow(	m_Properties.width, 
											m_Properties.height, 
											m_Properties.title.c_str(), 
											nullptr, nullptr);
		EN_ASSERT(m_WindowHandle);
		glfwMakeContextCurrent(m_WindowHandle);
		glewInit();
		
		glfwSetWindowUserPointer(m_WindowHandle, &m_Properties);
		SetVSync(true);

		glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow* window)
		{
			EN_DEBUGMSG("%s","[Event] Window closed");
			auto properties = static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));
			WindowClosedEvent event;
			properties->eventCallback(event);
		});

		glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			auto properties = static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));
			
			switch (action)
			{
				case GLFW_PRESS: 
				{
					EN_DEBUGMSG("%s%d%s","[Event] Key ",key," pressed");
					Keyboard::KeyPressedEvent event((Keyboard::KeyCode)key);
					properties->eventCallback(event);
					break;
				}
				case GLFW_RELEASE: 
				{
					EN_DEBUGMSG("%s%d%s", "[Event] Key ", key, " released");
					Keyboard::KeyReleasedEvent event((Keyboard::KeyCode)key);
					properties->eventCallback(event);
					break;
				}
			default: break;
			}
			
		});

		glfwSetMouseButtonCallback(m_WindowHandle, [](GLFWwindow* window, int button,  int action, int mods)
		{
			auto properties = static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
			{
				EN_DEBUGMSG("%s%d%s", "[Event] Mouse button ", button, " pressed");
				Mouse::MouseButtonPressedEvent event((Mouse::MouseButtonCode)button);
				properties->eventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				EN_DEBUGMSG("%s%d%s", "[Event] Mouse button ", button, " released");
				Mouse::MouseButtonPressedEvent event((Mouse::MouseButtonCode)button);
				properties->eventCallback(event);
				break;
			}
			default: break;
			}

		});

		glfwSetCursorPosCallback(m_WindowHandle, [](GLFWwindow* window, double xPos, double yPos)
		{
			EN_DEBUGMSG("%s%.0f%s%.0f%s", "[Event] Mouse moved to position (", xPos,",",yPos, ")");
			auto properties = static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));
			Mouse::MouseMovedEvent event(xPos,yPos);
			properties->eventCallback(event);
		});

		glfwSetErrorCallback(GLFWErrorCallback);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_WindowHandle);
		glfwTerminate();
	}

	std::shared_ptr<Window> Window::Create(const WindowProperties& props)
	{
		return std::make_shared<Window>(props);
	}

	void Window::OnUpdate(void)
	{
		glfwPollEvents();
		glfwSwapBuffers(m_WindowHandle);
	}

	void Window::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_Properties.VSync = enabled;
	}

	void Window::InitProperties(const WindowProperties& props)
	{
		m_Properties.title = props.title;
		m_Properties.width = props.width;
		m_Properties.height = props.height;
	}

}