#pragma once

#include "Core.h"
#include "../Events/Event.h"

namespace Engine
{
	using EventCallback = std::function<void(Event&)>;

	struct WindowProperties
	{
		std::string Title;
		unsigned Width;
		unsigned Height;
		EventCallback Callback;
		bool VSync;

		explicit WindowProperties(const std::string& title = "MyWindow", unsigned width = 1280, unsigned height = 720)
			:	Title(title),
				Width(width),
				Height(height),
				Callback(nullptr),
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
		static std::unique_ptr<Window> Create(const WindowProperties& props = WindowProperties());

		void OnUpdate(void);
	public:
		inline void SetEventCallback(const EventCallback& callback)	{ m_Properties.Callback = callback; }
		inline GLFWwindow* GetWindowHandle(void) const				{ return m_WindowHandle; }
		inline uint16_t GetHeight() const							{ return m_Properties.Height; }
		inline uint16_t GetWidth() const							{ return m_Properties.Width; }
		void SetVSync(bool enabled);
	};
}