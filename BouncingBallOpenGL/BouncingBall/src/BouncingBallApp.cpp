#include <Engine.h>
#include <Engine/Core/EntryPoint.h>

#define EN_DEBUG

class BouncingBallApplication : public Engine::Application
{
public:
	BouncingBallApplication()
		:	Engine::Application()
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
