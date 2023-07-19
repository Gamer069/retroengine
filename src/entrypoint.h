#pragma once

#include "app.h"
#include "logging.h"

extern RetroEngine::Application* RetroEngine::CreateApplication(); 

int main(int argc, char** argv) {
    RetroEngine::Logging::Init();
    
    auto application = RetroEngine::CreateApplication();
    application->Run();
    delete application;
    return 0;
}