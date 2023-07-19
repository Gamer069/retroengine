#pragma once

#include "event.h"

namespace RetroEngine {
    class KeyEvent: public Event {
        public:
            inline int GetKeycode() const { return m_Keycode; };
            
            CAT(EventCategory::Keyboard | EventCategory::Input)
        protected:
            KeyEvent(int keycode) : m_Keycode(keycode) {};
            int m_Keycode;
    };
    class KeyPressedEvent : public KeyEvent {
        public:
            KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}
            
            inline int GetRepeatCount() const { return m_RepeatCount; };
            
            std::string ToString() const override {
                std::stringstream stream;
                stream << "KeyPress: " << m_RepeatCount << " rep, " << m_Keycode;
                return stream.str();
            }
            
            TYPE(KeyPressed)
        
        protected:
            int m_RepeatCount;
    };
    class KeyReleasedEvent : public KeyEvent {
        public:
            KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}
            
            std::string ToString() const override {
                std::stringstream stream;
                stream << "KeyRelease: " << m_Keycode;
                return stream.str();
            }
            
            TYPE(KeyReleased)
    };
}