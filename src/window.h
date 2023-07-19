#pragma once

#include "ret_pch.h"

#include "event/event.h"

namespace RetroEngine {
    struct Win {
        std::string Title;
        unsigned int Width;
        unsigned int Height;
        
        Win(const std::string& title = "RetroEngine", unsigned int width = 1200, unsigned int height = 720) : Title(title), Width(width), Height(height) {}
    };
    
    class Window {
        public:
            using EventCallbackFn = std::function<void(Event&)>;
            
            virtual ~Window() {};
            virtual void Update() = 0;
            
            virtual unsigned int GetWidth() const = 0; 
            virtual unsigned int GetHeight() const = 0;
            
            virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
            virtual void SetVSync(bool vsync) = 0;
            virtual bool IsVSync() const = 0;
            
            static Window* Create(const Win& properties = Win());
    };
}