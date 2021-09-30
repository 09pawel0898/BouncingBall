#include "MainMenuState.h"
#include "Utility.h"
#include <algorithm>

MainMenuState::MainMenuState(En::States::StateManager& stateManager, Context context)
	:	State(stateManager, context)
{
	InitTextures();
	InitSprites();
}

void MainMenuState::OnRender(void) const
{
	En::Renderer::Draw(m_Background);
	
	static unsigned animFrame = 0;
	if (m_GameStarted)
	{
		En::Renderer::Draw(m_TransitionAnim[animFrame++]);
		if (animFrame == 6)
			App->GetStateManager()->PushState("Gameplay");
	}
	else
		En::Renderer::Draw(m_DarkTheme);

	En::Renderer::Draw(m_Logo);
	En::Renderer::Draw(m_PlayButton);

}

bool MainMenuState::OnUpdate(double deltaTime)
{
	if (IsButtonCovered<ButtonType::Round>(m_PlayButton, 72))
		m_PlayButton.SetScale(0.89f);
	else 
		m_PlayButton.SetScale(0.8f);
	return true;
}

bool MainMenuState::OnEvent(En::Event& event)
{
	En::EventDispatcher dispatcher(event);
	dispatcher.Dipatch<En::MouseButtonPressedEvent>(BIND_EVENT_FN(MainMenuState::OnMouseButtonPressed));

	return true;
}

bool MainMenuState::OnMouseButtonPressed(En::MouseButtonPressedEvent& event)
{
	if (IsButtonCovered<ButtonType::Round>(m_PlayButton, 72))
		m_GameStarted = true;
	return true;
}

void MainMenuState::InitTextures(void)
{
	const auto& texManager = App->GetTextureManager();
	texManager->LoadResource("background", "res/textures/bgpattern.png");
	//texManager->LoadResource("ball", "res/textures/ball.png");
	texManager->LoadResource("transAnim0", "res/textures/0.png");
	//texManager->LoadResource("backButton", "res/textures/buttonback.png");
	texManager->LoadResource("playButton", "res/textures/playbutton.png");
	texManager->LoadResource("logo", "res/textures/logoball.png");
	//texManager->LoadResource("tile", "res/textures/tile.png");
	//texManager->LoadResource("ballicon", "res/textures/ballicon.png");

	for (unsigned int i = 0; i < 6; i++)
	{
		auto id = std::to_string(i + 1);
		std::string path = "res/textures/" + id + ".png";
		texManager->LoadResource("transAnim"+ id, path);
	}
}

void MainMenuState::InitSprites(void)
{
	const auto& texManager = App->GetTextureManager();
	m_Background.SetTexture(texManager->GetResource("background"));

	m_Logo.SetTexture(texManager->GetResource("logo"));
	m_Logo.SetPosition({ 25,5 });
	m_Logo.SetScale(0.9f);
	
	m_PlayButton.SetTexture(texManager->GetResource("playButton"));
	m_PlayButton.SetOrigin({ 75, 75 });
	m_PlayButton.SetPosition({ App->GetWindow()->GetWidth() / 2.0f, 420 });

	m_DarkTheme.SetTexture(texManager->GetResource("transAnim0"));

	std::for_each(m_TransitionAnim.begin(), m_TransitionAnim.end(),
		[&, i = 0](En::Sprite& spr) mutable
		{
			spr.SetTexture(texManager->GetResource("transAnim" + std::to_string(++i)));
		});

}
