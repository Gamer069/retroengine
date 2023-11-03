#include "retroengine.h"

class ExampleLayer : public RetroEngine::Layer {
    public:
        ExampleLayer() : Layer("ExampleLayer") {}

        void OnUpdate() override {
            if (RetroEngine::Controls::IsKeyPressed(RET_KEY_TAB)) {
                RET_INFO("haha tab key mr pressed");
            }
        }

        void OnImGuiRender() override {
        }

        void OnEvent(RetroEngine::Event& event) override {
            RET_TRACE("{0}", event);
        }
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
