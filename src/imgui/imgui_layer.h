#pragma once

#include "event/app_event.h"
#include "event/key_event.h"
#include "layer.h"
#include "event/mouse_event.h"

namespace RetroEngine {
    class ImGuiLayer : public Layer {
        public:
            ImGuiLayer();
            ~ImGuiLayer();
            
            void OnAttach();
            void OnDetach();
            void OnUpdate();
            void OnEvent(Event& event);
        private:
            bool OnMousePressedEvent(MouseButtonEvent& e);
            bool OnMouseReleasedEvent(MouseReleaseEvent& e);
            bool OnMouseMovedEvent(MouseMovedEvent& e);
            bool OnMouseScrollEvent(MouseScrollEvent& e);
            
            bool OnKeyPressedEvent(KeyPressedEvent& e);
            bool OnKeyTypedEvent(KeyTypedEvent& e);
            bool OnKeyReleasedEvent(KeyReleasedEvent& e);
            
            bool OnWindowResizedEvent(WinResizeEvent& e);
          
            float m_Time = 0.0f;
    };
}