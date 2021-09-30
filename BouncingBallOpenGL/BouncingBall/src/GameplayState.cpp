#include "GameplayState.h"
#include "Utility.h"

GameplayState::GameplayState(En::States::StateManager& stateManager, Context context)
	: State(stateManager, context)
{
	InitTextures();
	InitSprites();
}

void GameplayState::OnRender(void) const
{
	En::Renderer::Draw(m_Background);
}

bool GameplayState::OnUpdate(double deltaTime)
{
	return true;
}

bool GameplayState::OnEvent(En::Event& event)
{
	En::EventDispatcher dispatcher(event);
	dispatcher.Dipatch<En::MouseButtonPressedEvent>(BIND_EVENT_FN(GameplayState::OnMouseButtonPressed));

	return true;
}

bool GameplayState::OnMouseButtonPressed(En::MouseButtonPressedEvent& event)
{
	//IsButtonCovered<ButtonType::Rectangular>()
	return true;
}

void GameplayState::InitTextures(void)
{
	const auto& texManager = App->GetTextureManager();
	texManager->LoadResource("ball", "res/textures/ball.png");
	//texManager->LoadResource("backButton", "res/textures/buttonback.png");
	//texManager->LoadResource("tile", "res/textures/tile.png");
	//texManager->LoadResource("ballicon", "res/textures/ballicon.png");
}

void GameplayState::InitSprites(void)
{
	const auto& texManager = App->GetTextureManager();
	m_Background.SetTexture(texManager->GetResource("background"));
}
