#include "retroengine.h"

class Sandbox: public RetroEngine::Application {
    public:
      Sandbox() {}
      ~Sandbox() {}
};

RetroEngine::Application* RetroEngine::CreateApplication() {
    return new Sandbox();
}