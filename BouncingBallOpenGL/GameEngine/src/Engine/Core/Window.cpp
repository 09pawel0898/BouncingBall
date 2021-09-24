#include "Window.h"

#include "../Events/WindowEvent.h"

namespace Engine
{
	Window::Window(const WindowProperties& props)
	{
		InitProperties(props);

		EN_ASSERT(glfwInit());

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, 0);

		m_WindowHandle = glfwCreateWindow(	m_Properties.Width, 
											m_Properties.Height, 
											m_Properties.Title.c_str(), 
											nullptr, nullptr);
		EN_ASSERT(m_WindowHandle);
		glfwMakeContextCurrent(m_WindowHandle);
		glewInit();
		
		glfwSetWindowUserPointer(m_WindowHandle, &m_Properties);
		SetVSync(true);

		glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow* window)
		{
			auto properties = static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));
			WindowClosedEvent event;
			properties->Callback(event);
		});

	}

	Window::~Window()
	{
		glfwDestroyWindow(m_WindowHandle);
		glfwTerminate();
	}

	std::unique_ptr<Window> Window::Create(const WindowProperties& props)
	{
		return std::make_unique<Window>(props);
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
		m_Properties.Title = props.Title;
		m_Properties.Width = props.Width;
		m_Properties.Height = props.Height;
	}

}