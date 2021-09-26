#pragma once

#include <memory>

#ifdef EN_BUILD
#include "../States/StateManager.h"
#include "../Resources/ResourceManager.h"
#else
#include "../Resources/ResourceIdentifiers.h"
#endif

namespace En
{
	class Window;
	class Event;
	class WindowClosedEvent;
}

namespace En
{
	class Application
	{
	private:
		std::shared_ptr<Window> m_Window;
		std::shared_ptr<TextureManager> m_TextureManager;
		std::unique_ptr<States::StateManager> m_StateManager;

		bool m_Running = true;
		double m_DeltaTime;

		Application(const Application& app) = delete;
		Application& operator =(const Application& app) = delete;

		void OnEvent(Event& event);
		bool OnWindowClosed(WindowClosedEvent& event);
	public:
		Application();
		virtual ~Application();

		void Run();
		inline double GetDT(void) const { return m_DeltaTime; }
		inline std::unique_ptr<States::StateManager>& GetStateManager(void) { return m_StateManager; }
	};

	std::shared_ptr<Application> CreateApplication();
}