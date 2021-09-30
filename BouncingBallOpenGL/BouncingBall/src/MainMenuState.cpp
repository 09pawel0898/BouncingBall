#include "MainMenuState.h"

MainMenuState::MainMenuState(En::States::StateManager& stateManager, Context context)
	:	State(stateManager, context)
{
	App->GetTextureManager()->LoadResource("Test", "res/textures/bgpattern.png");
}

void MainMenuState::OnRender(void) const
{
	En::Sprite spr(App->GetTextureManager()->GetResource("Test"));
	spr.SetPosition({ 120,120 });
	spr.SetSize({ 200,200 });

	En::Renderer::Draw(spr);

}

bool MainMenuState::OnUpdate(double deltaTime)
{
	return true;
}

bool MainMenuState::OnEvent(En::Event& event)
{
	En::EventDispatcher dispatcher(event);
	dispatcher.Dipatch<En::KeyPressedEvent>(BIND_EVENT_FN(MainMenuState::OnKeyPressed));

	return true;
}

bool MainMenuState::OnKeyPressed(En::KeyPressedEvent event)
{
	return true;
}
