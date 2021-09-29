#include "Application.h"
#include "Core.h"
#include "Debug.h"
#include "../Events/WindowEvent.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include <chrono>

namespace En
{
    std::shared_ptr<Application> Application::s_Instance = nullptr;

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dipatch<WindowClosedEvent>(BIND_APP_EVENT_FN(OnWindowClosed));

        if (event.Handled())
            return;
        m_StateManager->OnEvent(event);
    }

    bool Application::OnWindowClosed(WindowClosedEvent& event)
    {
        m_Running = false;
        return true;
    }

    Application::Application(const WindowProperties& windowProperties)
    {
        m_Window = Window::Create(windowProperties);
        m_TextureManager = std::make_shared<TextureManager>();
        m_Window->SetEventCallback(BIND_APP_EVENT_FN(OnEvent));
        m_StateManager = std::make_unique<States::StateManager>(States::State::Context( m_Window, m_TextureManager));
    }

    void Application::Run()
    {
        Renderer::Init(m_Window->GetWidth(), m_Window->GetHeight());
        Renderer::EnableBlending();

        while (m_Running)
        {
            auto tFrameStart = std::chrono::high_resolution_clock::now();
            Renderer::Clear();

            m_StateManager->OnUpdate(m_DeltaTime);
            m_StateManager->OnRender();

            auto tFrameEnd = std::chrono::high_resolution_clock::now();
            m_DeltaTime = std::chrono::duration<double, std::milli>
                (tFrameEnd - tFrameStart).count();

            m_Window->OnUpdate();
        }
    }
}