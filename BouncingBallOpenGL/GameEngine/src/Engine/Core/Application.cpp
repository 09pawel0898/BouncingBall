#include "Application.h"
#include "Core.h"
#include "Debug.h"
#include "../Events/WindowEvent.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include <chrono>
#include <thread>

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

        using TimePoint = std::chrono::high_resolution_clock;

        std::chrono::steady_clock::time_point tFrameStart,tLastUpdate;
        tLastUpdate = TimePoint::now();
        double tElapsedTime{ 0.0 };
        double tMinTimePerFrame = 1000.0 / m_FPSLIMIT;
     
        auto updateStats = [&]
        {
            m_DeltaTime = tElapsedTime;
            m_FPS = (1.0 / m_DeltaTime) * 1000;
        };

        while (m_Running)
        {
            tFrameStart = TimePoint::now();
            tElapsedTime = std::chrono::duration<double, std::milli>
                (tFrameStart - tLastUpdate).count();

            if (tElapsedTime >= tMinTimePerFrame)
            {
                Renderer::Clear();
                m_StateManager->OnUpdate(m_DeltaTime);
                m_StateManager->OnRender();
                m_Window->OnUpdate();
                tLastUpdate = TimePoint::now();
                updateStats();
            }
        }
    }
}