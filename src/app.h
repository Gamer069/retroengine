#pragma once

#include "layer_stack.h"
#include "window.h"
#include "event/app_event.h"
#include "layer.h"
#include "glad/glad.h"
#define GLFW_INLUDE_NONE
#include "GLFW/glfw3.h"

namespace RetroEngine {
    class Application {
        public:
            Application();
            virtual ~Application();
          
            void Run();
            void OnEvent(Event& event);

            void PushLayer(Layer* layer);
            void PushOverlay(Layer* layer);

            inline static Application& Get() { return *s_Instance; }
            inline Window& GetWindow() { return *m_Window; }
        private:
            bool OnWindowClose(WinCloseEvent& event);
            std::unique_ptr<Window> m_Window;
            bool m_Running = true;
            LayerStack m_LayerStack;

            static Application* s_Instance;
    };
    // define in client.
    Application* CreateApplication();
}
