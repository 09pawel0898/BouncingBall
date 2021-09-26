#include <Engine.h>
#include <Engine/Core/EntryPoint.h>

#include <iostream>

#define EN_DEBUG

class MainMenuState : public En::States::State
{
public:
	MainMenuState(En::States::StateManager& stateManager, Context context)
		:	State(stateManager,context)
	{}
	virtual ~MainMenuState() = default;

	virtual void OnRender(void) const override {}
	virtual bool OnUpdate(double deltaTime) override { std::cout << "Hello"; return true; }
	virtual bool OnEvent(En::Event& event) override { return true; }

};

class BouncingBallApplication : public En::Application
{
public:
	BouncingBallApplication()
		:	En::Application()
	{
		GetStateManager()->RegisterState<MainMenuState>("MainMenu");
		GetStateManager()->PushState("MainMenu");
	}

	~BouncingBallApplication()
	{}
};

std::shared_ptr<En::Application> En::CreateApplication(void)
{
	return std::make_shared<BouncingBallApplication>();
}
