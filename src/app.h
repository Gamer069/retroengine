#pragma once

#include "layer_stack.h"
#include "render/buf.h"
#include "render/array.h"
#include "window.h"
#include "event/app_event.h"
#include "layer.h"
#include <cstdint>
#define GLFW_INLUDE_NONE
#include "GLFW/glfw3.h"

#include "imgui/imgui_layer.h"

#include "render/opengl_shader.h"

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
            ImGuiLayer* m_ImGuiLayer;
            bool m_Running = true;
            LayerStack m_LayerStack;
            std::unique_ptr<VertexArray> m_VertexArray;
            std::unique_ptr<Shader> m_Shader;
            std::unique_ptr<VertexBuf> m_VertexBuf;
            std::unique_ptr<IndexBuf> m_IndexBuf;
            static Application* s_Instance;
    };
    // define in client.
    Application* CreateApplication();
}
