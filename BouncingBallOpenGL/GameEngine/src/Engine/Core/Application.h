#pragma once
#include <memory>

namespace Engine
{

	class Application
	{
	private:
		
	public:
		Application() {}
		virtual ~Application() {}

		void Run();
	};

	std::unique_ptr<Application> CreateApplication();
}