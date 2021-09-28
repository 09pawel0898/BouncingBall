#pragma once

#include <memory>

#include "Window.h"

#ifdef EN_BUILD
#include "../States/StateManager.h"
#include "../Resources/ResourceManager.h"
#else
#include "../Resources/ResourceIdentifiers.h"
#endif

namespace En
{
	class Event;
	class WindowClosedEvent;

	class Application
	{
	public:
		static Application* m_Instance;

		using WindwPtr = std::shared_ptr<Window>;
		using TextureManagerPtr = std::shared_ptr<TextureManager>;
		using StateManagerPtr = std::unique_ptr<States::StateManager>;

	private:
		WindwPtr m_Window;
		TextureManagerPtr m_TextureManager;
		StateManagerPtr m_StateManager;

		bool m_Running = true;
		double m_DeltaTime;

		Application(const Application& app) = delete;
		Application& operator =(const Application& app) = delete;

		void OnEvent(Event& event);
		bool OnWindowClosed(WindowClosedEvent& event);
	public:
		explicit Application(const WindowProperties& windowProperties = WindowProperties());
		virtual ~Application() = default;

		void Run();
		inline double GetDT(void) const { return m_DeltaTime; }
		inline const WindwPtr& GetWindow(void) const { return m_Window; }
		inline const StateManagerPtr& GetStateManager(void) const{ return m_StateManager; }
		inline const TextureManagerPtr& GetTextureManager(void) const{ return m_TextureManager; }
	};

	std::shared_ptr<Application> CreateApplication();
}