#include <OpenGL/OpenGL.h>
#include <cstdio>
#define GLFW_INCLUDE_NONE
#include "app.h"
#include "logging.h"

namespace RetroEngine {
    #define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        if (s_Instance) {
            RET_CORE_ERROR("Application already exists.");
        }
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        
        m_Window->SetEventCallback(BIND_FN(Application::OnEvent));
    }
    Application::~Application() {}
    
    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer) {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);
        
        dispatcher.Dispatch<WinCloseEvent>(BIND_FN(Application::OnWindowClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            (*--it)->OnEvent(event);
            if (event.IsHandled()) {
                break;
            }
        }
    }
    
    bool Application::OnWindowClose(WinCloseEvent& event) {
        m_Running = false;
        return true;
    }
    
    void Application::Run() {
        while (m_Running) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
            }

            m_Window->Update();
        }
    }
}