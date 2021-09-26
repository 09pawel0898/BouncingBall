#pragma once

#include "Core.h"
#include "../Events/Event.h"

namespace En
{
	using eventCallback = std::function<void(Event&)>;

	struct WindowProperties
	{
		std::string title;
		unsigned width;
		unsigned height;
		eventCallback eventCallback;
		bool VSync;

		WindowProperties(const std::string& title = "MyWindow", unsigned width = 1280, unsigned height = 720)
			:	title(title),
				width(width),
				height(height),
				eventCallback(nullptr),
				VSync(false)
		{}
	};

	class Window
	{
		
	public:
		Window(const WindowProperties& props);
		~Window();

	private:
		WindowProperties m_Properties;
		GLFWwindow* m_WindowHandle;

		void InitProperties(const WindowProperties& props);
	
	public:
		static std::shared_ptr<Window> Create(const WindowProperties& props = WindowProperties());
		void OnUpdate(void);
	
	public:
		inline void SetEventCallback(const eventCallback& callback)	{ m_Properties.eventCallback = callback; }
		inline GLFWwindow* GetWindowHandle(void) const				{ return m_WindowHandle; }
		inline uint16_t GetHeight() const							{ return m_Properties.height; }
		inline uint16_t GetWidth() const							{ return m_Properties.width; }
		
		void SetVSync(bool enabled);
	};
}