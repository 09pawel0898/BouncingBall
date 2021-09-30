#define EN_DEBUG

#include <Engine.h>
#include <Engine/Core/EntryPoint.h>
#include "MainMenuState.h"
#include <iostream>

class BouncingBallApplication : public En::Application
{
public:
	BouncingBallApplication()
		:	En::Application(En::WindowProperties("BouncingBall",640,480))
	{
		GetStateManager()->RegisterState<MainMenuState>("MainMenu");
		GetStateManager()->PushState("MainMenu");
	}

	~BouncingBallApplication() = default;
};

std::shared_ptr<En::Application> En::CreateApplication(void)
{
	return std::make_shared<BouncingBallApplication>();
}
