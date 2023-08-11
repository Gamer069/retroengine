#include "retroengine.h"

class ExampleLayer : public RetroEngine::Layer {
    public:
        ExampleLayer() : Layer("ExampleLayer") {}

        void OnEvent(RetroEngine::Event& event) override {
            RET_TRACE("{0}", event);
        }
};

class Sandbox: public RetroEngine::Application {
    public:
        Sandbox() {
            PushLayer(new ExampleLayer());
            PushOverlay(new RetroEngine::ImGuiLayer());
        }

        ~Sandbox() {}
};

RetroEngine::Application* RetroEngine::CreateApplication() {
    return new Sandbox();
}
