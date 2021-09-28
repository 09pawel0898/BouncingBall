#define EN_DEBUG

#include <Engine.h>
#include <Engine/Core/EntryPoint.h>

#include <iostream>

class MainMenuState : public En::States::State
{
public:
	MainMenuState(En::States::StateManager& stateManager, Context context)
		:	State(stateManager,context)
	{}
	virtual ~MainMenuState() = default;

	virtual void OnRender(void) const override 
	{
	
	}

	virtual bool OnUpdate(double deltaTime) override 
	{ 
		return true; 
	}

	virtual bool OnEvent(En::Event& event) override 
	{ 
		En::EventDispatcher dispatcher(event);
		dispatcher.Dipatch<En::KeyPressedEvent>(BIND_EVENT_FN(MainMenuState::OnKeyPressed));

		return true;
	}

	bool OnKeyPressed(En::KeyPressedEvent event)
	{
		return true;
	}
};

class BouncingBallApplication : public En::Application
{
public:
	BouncingBallApplication()
		:	En::Application(En::WindowProperties("BouncingBall",640,480))
	{
		GetStateManager()->RegisterState<MainMenuState>("MainMenu");
		GetStateManager()->PushState("MainMenu");

		En::Sprite sprite;
		//En::Application::TextureManagerPtr ptr = GetTextureManager()->
	}

	~BouncingBallApplication() = default;
};

std::shared_ptr<En::Application> En::CreateApplication(void)
{
	return std::make_shared<BouncingBallApplication>();
}
