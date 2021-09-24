#include "Application.h"
#include "Window.h"

Engine::Application::Application()
{
    m_Window = std::unique_ptr<Window>(Window::Create());
}

Engine::Application::~Application()
{
}

void Engine::Application::Run()
{
    while (m_Running) 
    {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        m_Window->OnUpdate();
    }
}
