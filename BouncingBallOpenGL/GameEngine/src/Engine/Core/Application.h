#pragma once

#include <memory>

#include "Window.h"

#include "../States/StateManager.h"
#include "../Resources/ResourceManager.h"

int main(void);

namespace En
{
	class Event;
	class WindowClosedEvent;

	class Application
	{
	private:
		friend int ::main(void);
		static std::shared_ptr<Application> s_Instance;

		using WindwPtr = std::shared_ptr<Window>;
		using TextureManagerPtr = std::shared_ptr<TextureManager>;
		using StateManagerPtr = std::unique_ptr<States::StateManager>;

	public:
		static std::shared_ptr<Application>& GetInstance(void) { return s_Instance; };

	private:
		WindwPtr m_Window;
		TextureManagerPtr m_TextureManager;
		StateManagerPtr m_StateManager;

		bool m_Running = true;
		double m_DeltaTime = 0.0;

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