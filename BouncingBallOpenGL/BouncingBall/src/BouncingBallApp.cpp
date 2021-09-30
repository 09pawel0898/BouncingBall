#define EN_DEBUG

#include <Engine.h>
#include <Engine/Core/EntryPoint.h>

#include "MainMenuState.h"
#include "GameplayState.h"


class BouncingBallApplication : public En::Application
{
public:
	BouncingBallApplication()
		:	En::Application(En::WindowProperties("BouncingBall",450,600))
	{
		SetFPSLimit(60);
		GetStateManager()->RegisterState<MainMenuState>("MainMenu");
		GetStateManager()->RegisterState<GameplayState>("Gameplay");
		GetStateManager()->PushState("MainMenu");
	}

	~BouncingBallApplication() = default;
};

std::shared_ptr<En::Application> En::CreateApplication(void)
{
	return std::make_shared<BouncingBallApplication>();
}
