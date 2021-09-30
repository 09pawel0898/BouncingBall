#pragma once

#include <Engine.h>
#include "Ball.h"

class GameplayState : public En::States::State
{
private:
	std::shared_ptr<En::Application>& App = En::Application::GetInstance();

private:
	En::Sprite m_Background, m_BackButton;
	Ball m_Ball;
	unsigned m_FrameCounter, m_LastJumpFrame;
	bool m_GameLost;

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
	void InitBall(void);
	void GoToMainMenu(void);
};