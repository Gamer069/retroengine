#pragma once

#include "ret_pch.h"

namespace RetroEngine {
    #define BIT(x) (1 << x)
    #define TYPE(type) static EventType GetStaticType() { return EventType::type; }\
    								virtual EventType GetType() const override { return GetStaticType(); }\
    								virtual const char* GetName() const override { return #type; }

    #define CAT(cat) virtual int GetCategoryFlags() const override { return cat; }
    enum class EventType {
        None = 0,
        WinClose, WinResize, WinFocus, WinLoseFocus, WinMove,
        Tick, Update, Render,
        KeyPressed, KeyReleased, KeyTyped,
        MousePress, MouseRelease, MouseMove, MouseScroll
    };
    
    enum EventCategory {
        None = 0,
        App = BIT(0),
        Input = BIT(1),
        Keyboard = BIT(2),
        Mouse = BIT(3),
        MouseBtn = BIT(4)
    };
    
    class Event {
        friend class EventDispatcher;
    public:
        virtual EventType GetType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }
    
        inline bool IsRelated(EventCategory cat) {
            return GetCategoryFlags() & cat;
        }

        inline bool IsHandled() { return m_Handled; }

    protected:
        bool m_Handled = false;
    };
    
    class EventDispatcher {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
      
        public:
            EventDispatcher(Event& event) : m_Event(event) {}
            
            template<typename T>
            bool Dispatch(EventFn<T> func) {
                if (m_Event.GetType() == T::GetStaticType()) {
                    m_Event.m_Handled = func(*(T*)&m_Event);
                    return true;
                }
                return false;
            }
        private:
            Event& m_Event;
    };
    
    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.ToString();
    }
}
