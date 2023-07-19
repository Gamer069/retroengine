#pragma once

#include "event.h"

namespace RetroEngine {
    class WinResizeEvent : public Event {
        public:
            WinResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {};
            
            inline unsigned int GetWidth() { return m_Width; }
            inline unsigned int GetHeight() { return m_Height; }
            
            std::string ToString() const override {
                std::stringstream stream;
                stream << "WinResize: " << m_Width << ", " << m_Height;
                return stream.str();
            }
            
            
            TYPE(WinResize)
            CAT(EventCategory::App)
        private:
            unsigned int m_Width, m_Height;
    };
    class WinCloseEvent : public Event {
        public:
            WinCloseEvent() {};
            
            TYPE(WinClose)
            CAT(EventCategory::App)
    };
    class TickEvent : public Event {
        public:
            TickEvent() {};
            
            TYPE(Tick)
            CAT(EventCategory::App)
    };
    class UpdateEvent : public Event {
        public:
            UpdateEvent() {};
            
            TYPE(Update)
            CAT(EventCategory::App)
    };
    class RenderEvent : public Event {
        public:
            RenderEvent() {};
            
            TYPE(Render)
            CAT(EventCategory::App)
    };
}