#pragma once

#include <Engine.h>

class GameLostState : public En::States::State
{
private:
	std::shared_ptr<En::Application>& App = En::Application::GetInstance();

private:
	En::Sprite m_Background, m_BackButton, m_RestartButton;
	En::Sprite m_LeftBallIcon, m_RightBallIcon, m_RestartText;

public:
	GameLostState(En::States::StateManager& stateManager, Context context);
	virtual ~GameLostState() = default;

	virtual void OnRender(void) const override;
	virtual bool OnUpdate(double deltaTime) override;
	virtual bool OnEvent(En::Event& event) override;

private:
	bool OnMouseButtonPressed(En::MouseButtonPressedEvent& event);

private:
	void InitTextures(void);
	void InitSprites(void);
	void GoToMainMenu(void);
	void RestartGame(void);
};