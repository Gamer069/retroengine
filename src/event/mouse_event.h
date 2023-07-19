#pragma once

#include "event.h"

namespace RetroEngine {
    class MouseMovedEvent: public Event {
        public:
            MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}
            
            inline float GetX() { return m_MouseX; }
            inline float GetY() { return m_MouseY; }
            
            std::string ToString() const override {
                std::stringstream stream;
                stream << "MouseMoved: " << m_MouseX << ", " << m_MouseY;
                return stream.str();
            }
            
            TYPE(MouseMove)
            CAT(EventCategory::Mouse | EventCategory::Input)
        protected:
            float m_MouseX, m_MouseY;
    };
    class MouseScrollEvent: public Event {
        public:
            MouseScrollEvent(float x_offset, float y_offset) : m_OffsetX(x_offset), m_OffsetY(y_offset) {}
            
            inline float GetXOffset() { return m_OffsetX; }
            inline float GetYOffset() { return m_OffsetY; }
            
            std::string ToString() const override {
                std::stringstream stream;
                stream << "MouseMoved: " << m_OffsetX << ", " << m_OffsetY;
                return stream.str();
            }
            
            TYPE(MouseScroll)
            CAT(EventCategory::Mouse | EventCategory::Input)
        protected:
            float m_OffsetX, m_OffsetY;
    };
    class MouseButtonEvent: public Event {
        public:
            inline int GetButton() { return m_Btn; }
            
            CAT(EventCategory::Mouse | EventCategory::Input)
        protected:
            MouseButtonEvent(int btn) : m_Btn(btn) {};
            
            int m_Btn;      
    };
    class MousePressEvent: public MouseButtonEvent {
        public:
            MousePressEvent(int btn) : MouseButtonEvent(btn) {}
            
            std::string ToString() const override {
                std::stringstream stream;
                stream << "MousePress: " << m_Btn;
                return stream.str();
            }
            
            TYPE(MousePress)
            CAT(EventCategory::Mouse | EventCategory::Input)
    };
    class MouseReleaseEvent: public MouseButtonEvent {
        public:
            MouseReleaseEvent(int btn) : MouseButtonEvent(btn) {}
            
            std::string ToString() const override {
                std::stringstream stream;
                stream << "MouseRelease: " << m_Btn;
                return stream.str();
            }
            
            TYPE(MouseRelease)
            CAT(EventCategory::Mouse | EventCategory::Input)
    };
}