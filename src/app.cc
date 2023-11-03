#include "render/buf.h"
#include <glad/glad.h>
#include <cstdio>
#define GLFW_INCLUDE_NONE
#include "app.h"
#include "logging.h"
#include "inp.h"

#include "render/array.h"
#include "render/buf.h"

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

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        // vertex array
        m_VertexArray.reset(VertexArray::Create());
        // vertex buf
        float vert[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };
        m_VertexBuf.reset(VertexBuf::Create(vert, sizeof(vert)));
        
        BufLayout layout = {
            { GLSLType::Vec3, (char*)"a_Position" }
        };
        for (uint32_t i = 0; i < layout.GetElements().size(); i++) {
            BufElement element = layout.GetElements()[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.GetComponentCount(), element.GetBaseType(), element.IsNormalized() ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.offset);  
        }
        
        m_VertexBuf->SetLayout(layout);
        // index buf
        uint32_t indices[3] = { 0, 1, 2 };
        m_IndexBuf.reset(IndexBuf::Create(indices, sizeof(indices) / sizeof(uint32_t))); 
        // GLSL shaders
        std::string vertShader = R"(
            #version 330 core
    
            layout(location = 0) in vec3 a_Position;

            void main() {
                gl_Position = vec4(a_Position, 1.0);
            }
        )";
        std::string fragShader = R"(
            #version 330 core

            layout(location = 0) out vec4 a_Color;
    
            void main() {
                a_Color = vec4(1.0, 0.0, 0.0, 1.0);
            }
        )";
        m_Shader.reset(new Shader(vertShader, fragShader));
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
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();

            glBindVertexArray(m_VertexArray->GetID());
            glDrawElements(GL_TRIANGLES, m_IndexBuf->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
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
