#pragma once

#include <Engine.h>

class MainMenuState : public En::States::State
{
private:
	std::shared_ptr<En::Application>& App = En::Application::GetInstance();

public:
	MainMenuState(En::States::StateManager& stateManager, Context context);
	virtual ~MainMenuState() = default;

	virtual void OnRender(void) const override;
	virtual bool OnUpdate(double deltaTime) override;
	virtual bool OnEvent(En::Event& event) override;
	bool OnKeyPressed(En::KeyPressedEvent event);
};