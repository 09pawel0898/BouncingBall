#pragma once

#include <Engine.h>
#include <array>

class MainMenuState : public En::States::State
{
private:
	std::shared_ptr<En::Application>& App = En::Application::GetInstance();

private:
	En::Sprite m_Background;
	En::Sprite m_Logo;
	En::Sprite m_PlayButton;
	En::Sprite m_DarkTheme;
	std::array<En::Sprite,6> m_TransitionAnim;

	bool m_GameStarted = false;
public:
	MainMenuState(En::States::StateManager& stateManager, Context context);
	virtual ~MainMenuState() = default;

	virtual void OnRender(void) const override;
	virtual bool OnUpdate(double deltaTime) override;
	virtual bool OnEvent(En::Event& event) override;
	virtual void OnAwake(void) override;

private:
	bool OnMouseButtonPressed(En::MouseButtonPressedEvent& event);

private:
	void InitTextures(void);
	void InitSprites(void);
};