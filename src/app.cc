#include "GLFW/glfw3.h"

#include "app.h"
#include "logging.h"
#include "ret_pch.h"

namespace RetroEngine {
    #define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)
    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
        
        m_Window->SetEventCallback(BIND_FN(Application::OnEvent));
    }
    Application::~Application() {}
    
    void Application::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);
        
        dispatcher.Dispatch<WinCloseEvent>(BIND_FN(Application::OnWindowClose));
        
        RET_CORE_TRACE("EVENT: {0}", event.ToString());
    }
    
    bool Application::OnWindowClose(WinCloseEvent& event) {
        m_Running = false;
        return true;
    }
    
    void Application::Run() {
        while (m_Running) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->Update();
        }
    }
}