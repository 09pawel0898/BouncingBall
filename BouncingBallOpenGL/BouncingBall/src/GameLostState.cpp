#include "GameLostState.h"
#include "Utility.h"

GameLostState::GameLostState(En::States::StateManager& stateManager, Context context)
	: State(stateManager, context)
{
	InitTextures();
	InitSprites();
}

void GameLostState::OnRender(void) const
{
	En::Renderer::Draw(m_Background);
	//En::Renderer::Draw(m_Score);
	En::Renderer::Draw(m_RestartButton);
	En::Renderer::Draw(m_LeftBallIcon);
	En::Renderer::Draw(m_RightBallIcon);
	En::Renderer::Draw(m_BackButton);
	En::Renderer::Draw(m_RestartText);
}

bool GameLostState::OnUpdate(double deltaTime)
{
	if (IsButtonCovered<ButtonType::Round>(m_BackButton, 30))
		m_BackButton.SetScale(0.64f);
	else
		m_BackButton.SetScale(0.55f);

	if (IsButtonCovered<ButtonType::Rectangular>(m_RestartButton) && m_RestartButton.GetPosition().y == 400)
	{
		m_LeftBallIcon.SetPosition({ 130, 427 });
		m_RightBallIcon.SetPosition({ 320, 427 });
		m_LeftBallIcon.Rotate(1);
		m_RightBallIcon.Rotate(-1);
	}
	else
	{
		m_LeftBallIcon.SetPosition({ 700, 700 });
		m_RightBallIcon.SetPosition({700, 700});
	}

	if (m_RestartButton.GetPosition().y > 400)
	{
		m_RestartButton.SetPosition({m_RestartButton.GetPosition().x,
									 m_RestartButton.GetPosition().y - 10});
		m_RestartText.SetPosition({	m_RestartText.GetPosition().x,
									m_RestartText.GetPosition().y - 10 });
	}
	return true;
}

bool GameLostState::OnEvent(En::Event& event)
{
	En::EventDispatcher dispatcher(event);
	dispatcher.Dipatch<En::MouseButtonPressedEvent>(BIND_EVENT_FN(GameLostState::OnMouseButtonPressed));

	return true;
}

bool GameLostState::OnMouseButtonPressed(En::MouseButtonPressedEvent& event)
{
	if (IsButtonCovered<ButtonType::Round>(m_BackButton, 48))
		GoToMainMenu();
	else if (IsButtonCovered<ButtonType::Rectangular>(m_RestartButton))
		RestartGame();

	return true;
}

void GameLostState::InitTextures(void)
{
	const auto& texManager = App->GetTextureManager();
	texManager->LoadResource("tile", "res/textures/tile.png");
	texManager->LoadResource("ballicon", "res/textures/ballicon.png");
	texManager->LoadResource("restarttext", "res/textures/restarttext.png");
}

void GameLostState::InitSprites(void)
{
	const auto& texManager = App->GetTextureManager();
	m_Background.SetTexture(texManager->GetResource("background"));
	m_BackButton.SetTexture(texManager->GetResource("backButton"));
	m_BackButton.SetOrigin({ 48,48 });
	m_BackButton.SetScale(0.6f);
	m_BackButton.SetPosition({ 400,50 });
	m_RestartButton.SetTexture(texManager->GetResource("tile"));
	m_RestartButton.SetPosition({0,600});
	m_RestartText.SetTexture(texManager->GetResource("restarttext"));
	m_RestartText.SetPosition({ 0,600 });

	auto iconConf = [&](auto& icon)
	{
		icon.SetTexture(texManager->GetResource("ballicon"));
		icon.SetOrigin({ 42, 42 });
		icon.SetScale(0.5f);
	};
	iconConf(m_LeftBallIcon);
	iconConf(m_RightBallIcon);
}

void GameLostState::GoToMainMenu(void)
{
	App->GetStateManager()->PopState();
	App->GetStateManager()->PopState();
}

void GameLostState::RestartGame(void)
{
	App->GetStateManager()->PopState();
}