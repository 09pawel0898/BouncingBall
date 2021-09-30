#define EN_DEBUG

#include <Engine.h>
#include <Engine/Core/EntryPoint.h>

#include "MainMenuState.h"
#include "GameplayState.h"
#include "GameLostState.h"

class BouncingBallApplication : public En::Application
{
public:
	BouncingBallApplication()
		:	En::Application(En::WindowProperties("BouncingBall",450,600))
	{
		SetFPSLimit(120);
		GetStateManager()->RegisterState<MainMenuState>("MainMenu");
		GetStateManager()->RegisterState<GameplayState>("Gameplay");
		GetStateManager()->RegisterState<GameLostState>("GameLost");
		GetStateManager()->PushState("MainMenu");
	}

	~BouncingBallApplication() = default;
};

std::shared_ptr<En::Application> En::CreateApplication(void)
{
	return std::make_shared<BouncingBallApplication>();
}
