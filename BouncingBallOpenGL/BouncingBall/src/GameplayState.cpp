#include "GameplayState.h"
#include "Utility.h"

GameplayState::GameplayState(En::States::StateManager& stateManager, Context context)
	:	State(stateManager, context),
		m_FrameCounter(0),
		m_LastJumpFrame(0)
{
	InitTextures();
	InitSprites();
	InitBall();
}

void GameplayState::OnRender(void) const
{
	En::Renderer::Draw(m_Background);
	En::Renderer::Draw(m_Ball);
	En::Renderer::Draw(m_BackButton);
}

bool GameplayState::OnUpdate(double deltaTime)
{
	if (IsButtonCovered<ButtonType::Round>(m_BackButton, 30))
		m_BackButton.SetScale(0.64f);
	else
		m_BackButton.SetScale(0.55f);

	if (m_Ball.m_IsJumping && (m_LastJumpFrame == m_FrameCounter - 30))
		m_Ball.m_IsJumping = false;

	//this->jc = std::to_string(this->ball.jump_counter);

	/*
	if (this->jc.size() == 1)
		this->shift = 25;
	else if (this->jc.size() > 1)
	{
		if (this->jc.size() == 2)
			this->shift = 47;
		else this->shift = 69;
	}
	*/
	
	if (m_Ball.GetPosition().y - 1000 > App->GetWindow()->GetHeight())
	{
		m_GameLost = true;
		App->GetStateManager()->PushState("GameLost");
	}
	/* 
	this->COUNTER.setPosition(this->window->getSize().x / 2.0f - this->shift, 138);
	this->COUNTER.setString(this->jc);
	*/
	static RectangleShape leftWall{ {0,0}, {2,600} };
	static RectangleShape rightWall{ {448,0}, {2,600} };

	m_Ball.Update(leftWall, rightWall);

	m_FrameCounter++;
	return true;
}

bool GameplayState::OnEvent(En::Event& event)
{
	En::EventDispatcher dispatcher(event);
	dispatcher.Dipatch<En::MouseButtonPressedEvent>(BIND_EVENT_FN(GameplayState::OnMouseButtonPressed));

	return true;
}

void GameplayState::OnAwake(void)
{
	m_GameLost = false;
	m_Ball.Reset();
}

bool GameplayState::OnMouseButtonPressed(En::MouseButtonPressedEvent& event)
{
	if (m_Ball.IsBallClicked())
	{
		if (!m_Ball.m_IsJumping)
		{
			m_Ball.m_JumpCounter++;
			m_Ball.Jump();
			m_LastJumpFrame = m_FrameCounter;
			m_Ball.m_IsJumping = true;
			return true;
		}
	}

	
	if (IsButtonCovered<ButtonType::Round>(m_BackButton, 48))
		GoToMainMenu();
	return true;
}

void GameplayState::InitTextures(void)
{
	const auto& texManager = App->GetTextureManager();
	texManager->LoadResource("ball", "res/textures/ball.png");
	texManager->LoadResource("backButton", "res/textures/buttonback.png");
	//texManager->LoadResource("tile", "res/textures/tile.png");
	//texManager->LoadResource("ballicon", "res/textures/ballicon.png");
}

void GameplayState::InitSprites(void)
{
	const auto& texManager = App->GetTextureManager();
	m_Background.SetTexture(texManager->GetResource("background"));
	m_BackButton.SetTexture(texManager->GetResource("backButton"));
	m_BackButton.SetOrigin({48,48});
	m_BackButton.SetScale(0.6f);
	m_BackButton.SetPosition({400,50});
}

void GameplayState::InitBall(void)
{
	const auto& texManager = App->GetTextureManager();
	m_Ball.SetTexture(texManager->GetResource("ball"));
	m_Ball.SetPosition({App->GetWindow()->GetWidth() /2,150});
	m_Ball.SetOrigin({ 43,43 });
}

void GameplayState::GoToMainMenu(void)
{
	App->GetStateManager()->PopState();
}