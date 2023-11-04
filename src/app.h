#pragma once

#include "layer_stack.h"
#include "util/time.h"
#include "window.h"
#include "event/app_event.h"
#include "layer.h"
#include <cstdint>

#include "imgui/imgui_layer.h"

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
        private:
            std::unique_ptr<Window> m_Window;
            ImGuiLayer* m_ImGuiLayer;
            bool m_Running = true;
            LayerStack m_LayerStack;
            float m_LastFrame = 0.0f;
        private:
            static Application* s_Instance;
    };
    // define in client.
    Application* CreateApplication();
}
