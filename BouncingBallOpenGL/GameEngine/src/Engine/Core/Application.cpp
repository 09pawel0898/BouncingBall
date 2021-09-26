#include "Application.h"
#include "Window.h"
#include "Core.h"
#include "../Events/WindowEvent.h"

#include <chrono>

namespace En
{
    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dipatch<WindowClosedEvent>(BIND_EVENT_FN(OnWindowClosed));
    }

    bool Application::OnWindowClosed(WindowClosedEvent& event)
    {
        m_Running = false;
        return true;
    }

    Application::Application()
    {
        m_Window = Window::Create();
        m_TextureManager = std::make_shared<TextureManager>();
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
        m_StateManager = std::make_unique<States::StateManager>(States::State::Context( m_Window,                                                                        m_TextureManager));
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            auto tFrameStart = std::chrono::high_resolution_clock::now();
            m_Window->OnUpdate();

            m_StateManager->OnUpdate(m_DeltaTime);
            m_StateManager->OnRender();

            auto tFrameEnd = std::chrono::high_resolution_clock::now();
            m_DeltaTime = std::chrono::duration<double, std::milli>
                (tFrameEnd - tFrameStart).count();
        }
    }
}