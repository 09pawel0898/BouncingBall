#include "Application.h"
#include "Core.h"
#include "Debug.h"
#include "../Events/WindowEvent.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include <chrono>

namespace En
{
    Application* Application::m_Instance = nullptr;

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dipatch<WindowClosedEvent>(BIND_EVENT_FN(OnWindowClosed));

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
        if (Application::m_Instance == nullptr)
            Application::m_Instance = this;

        m_Window = Window::Create(windowProperties);
        m_TextureManager = std::make_shared<TextureManager>();
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
        m_StateManager = std::make_unique<States::StateManager>(States::State::Context( m_Window, m_TextureManager));
    }

    void Application::Run()
    {

        std::vector<float> positions = { -0.5f, -0.5f, 0.0f, 0.0f,
                                     0.5f, -0.5f, 1.0f, 0.0f,
                                     0.5f,  0.5f, 1.0f, 1.0f,
                                    -0.5f,  0.5f, 0.0f, 1.0f };

        std::vector<uint32_t> indices = { 0,1,2,
                                           2,3,0 };

        VertexArray vertexArray;

        // specifying buffer
        VertexBuffer vertexBuffer(positions, 4 * 4 * sizeof(float));

        // specifying layout
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        vertexArray.AddBuffer(vertexBuffer, layout);

        //std::cout << std::is_same<uint32_t, uint32_t>::value;
        IndexBuffer indexBuffer(indices);

        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

        // setting shader
        Shader shader("res/shaders/basic.shader");
        shader.Bind();
        shader.SetUniform1i("u_Texture", 0);
        shader.SetUniformMat4f("u_MVP", proj);
        // setting uniform parameter

        Texture texture("res/textures/texture.png");
        texture.Bind(0);

        Renderer renderer;
        renderer.EnableBlending();

        while (m_Running)
        {
            auto tFrameStart = std::chrono::high_resolution_clock::now();
            renderer.Clear();

            m_StateManager->OnUpdate(m_DeltaTime);
            m_StateManager->OnRender();

            renderer.Draw(vertexArray, indexBuffer, shader);



            auto tFrameEnd = std::chrono::high_resolution_clock::now();
            m_DeltaTime = std::chrono::duration<double, std::milli>
                (tFrameEnd - tFrameStart).count();

            m_Window->OnUpdate();
        }
    }
}