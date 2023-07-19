#pragma once

#include "window.h"
#include "event/app_event.h"

namespace RetroEngine {
    class Application {
        public:
            Application();
            virtual ~Application();
          
            void Run();
            void OnEvent(Event& event);
        private:
            bool OnWindowClose(WinCloseEvent& event);
            std::unique_ptr<Window> m_Window;
            bool m_Running = true;
    };
    // define in client.
    Application* CreateApplication();
}