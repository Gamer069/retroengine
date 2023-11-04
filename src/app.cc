#include "render/buf.h"
#include "render/render_utils.h"
#include <glad/glad.h>
#include <cstdio>
#include "app.h"
#include "logging.h"
#include "inp.h"

#include "render/array.h"
#include "render/buf.h"
#include "render/renderer.h"

// TODO: put everything PLATFORM-SPECIFIC about delta time, etc. inside util/opengl
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace RetroEngine {
    Application* Application::s_Instance = nullptr;

    Application::Application() {
        if (s_Instance) {
            RET_CORE_ERROR("Application already exists.");
        }
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        
        m_Window->SetEventCallback(BIND_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
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
            float time = (float)glfwGetTime();
            Time timestep = time - m_LastFrame; 
            m_LastFrame = time;
            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate(timestep);
            }

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack) {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            m_Window->Update();
        }
    }
}
