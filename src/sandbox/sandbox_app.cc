#include "retroengine.h"

class ExampleLayer : public RetroEngine::Layer {
    public:
        ExampleLayer() : Layer("ExampleLayer"), m_Cam(-1.0f, 1.0f, -1.0f, 1.0f), m_CamPos(0.0f), m_TrianglePos(0.0f) {
            // vertex array
            m_VertexArray.reset(RetroEngine::VertexArray::Create());
            // vertex buf
            float vert[3 * 4] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f
            };
            m_VertexBuf.reset(RetroEngine::VertexBuf::Create(vert, sizeof(vert)));

            RetroEngine::BufLayout layout = {
                { RetroEngine::GLSLType::Vec3, (char*)"a_Position" }
            };
            m_VertexBuf->SetLayout(layout);
            m_VertexArray->AddVertexBuffer(m_VertexBuf);
            // index buf
            uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
            m_IndexBuf.reset(RetroEngine::IndexBuf::Create(indices, sizeof(indices) / sizeof(uint32_t)));
            m_VertexArray->SetIndexBuffer(m_IndexBuf);
            // GLSL shaders
            std::string vertShader = R"(
                #version 330 core
            
                layout(location = 0) in vec3 a_Position;

                uniform mat4 u_PV;
                uniform mat4 u_Transform;

                void main() {
                    gl_Position = u_PV * u_Transform * vec4(a_Position, 1.0);
                }
            )";
            std::string fragShader = R"(
                #version 330 core

                layout(location = 0) out vec4 a_Color;

                void main() {
                    a_Color = vec4(1.0, 0.0, 0.0, 1.0);
                }
            )";
            m_Shader.reset(new RetroEngine::Shader(vertShader, fragShader));
        }

        void OnUpdate(RetroEngine::Time ts) override {
            if (RetroEngine::Controls::IsKeyPressed(RET_KEY_I)) {
                m_TrianglePos.y += m_Speed * ts;
            }
            if (RetroEngine::Controls::IsKeyPressed(RET_KEY_K)) {
                m_TrianglePos.y -= m_Speed * ts; 
            }
            if (RetroEngine::Controls::IsKeyPressed(RET_KEY_J)) {
                m_TrianglePos.x -= m_Speed * ts;
            }
            if (RetroEngine::Controls::IsKeyPressed(RET_KEY_L)) {
                m_TrianglePos.x += m_Speed * ts;
            }
          
            RetroEngine::RenderUtils::ClearCol({0,0,0,1});
            RetroEngine::RenderUtils::Clear();

            RetroEngine::Renderer::BeginScene(m_Cam);
            Transform transform = glm::translate(glm::mat4(1.0f), m_TrianglePos);
            RetroEngine::Renderer::Submit(m_Shader, m_VertexArray, transform);
            RetroEngine::Renderer::EndScene();
        }

        void OnImGuiRender() override {
        }

        void OnEvent(RetroEngine::Event& event) override {
        }
    private:
        std::shared_ptr<RetroEngine::VertexArray> m_VertexArray;
        std::shared_ptr<RetroEngine::Shader> m_Shader;
        std::shared_ptr<RetroEngine::VertexBuf> m_VertexBuf;
        std::shared_ptr<RetroEngine::IndexBuf> m_IndexBuf;
        RetroEngine::OrthographicCamera m_Cam;
        glm::vec3 m_CamPos;
        glm::vec3 m_TrianglePos;
        float m_Speed = 1.0f;
};

class Sandbox: public RetroEngine::Application {
    public:
        Sandbox() {
            PushLayer(new ExampleLayer());
        }

        ~Sandbox() {}
};

RetroEngine::Application* RetroEngine::CreateApplication() {
    return new Sandbox();
}
