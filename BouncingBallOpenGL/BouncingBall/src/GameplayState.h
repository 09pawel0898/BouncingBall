#pragma once

#include <Engine.h>

class GameplayState : public En::States::State
{
private:
	std::shared_ptr<En::Application>& App = En::Application::GetInstance();

private:
	En::Sprite m_Background;

public:
	GameplayState(En::States::StateManager& stateManager, Context context);
	virtual ~GameplayState() = default;

	virtual void OnRender(void) const override;
	virtual bool OnUpdate(double deltaTime) override;
	virtual bool OnEvent(En::Event& event) override;

private:
	bool OnMouseButtonPressed(En::MouseButtonPressedEvent& event);

private:
	void InitTextures(void);
	void InitSprites(void);
};