#pragma once
#include <memory>



namespace Engine
{
	class Window;

	class Application
	{
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		Application(const Application& app) = delete;
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	std::unique_ptr<Application> CreateApplication();
}