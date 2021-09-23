#include <Engine.h>

#define EN_DEBUG
#include <Engine/Core/EntryPoint.h>

class BouncingBallApplication : public Engine::Application
{
public:
	BouncingBallApplication()
	{

	}

	~BouncingBallApplication()
	{

	}
};

std::unique_ptr<Engine::Application> Engine::CreateApplication(void)
{
	return std::make_unique<BouncingBallApplication>();
}
