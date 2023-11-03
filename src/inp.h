#pragma once

#include "key.h"

typedef std::pair<float, float> MousePos;

namespace RetroEngine {
    class Controls {
        public:
            /* TODO: stop using GLFW keycodes */
            inline static bool IsKeyPressed(int key) { return s_Instance->IsKeyPressedImpl(key); }
            inline static bool IsMousePressed(int btn) { return s_Instance->IsMousePressedImpl(btn); }
            inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
            inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
            inline static MousePos GetMousePos() { return s_Instance->GetMousePosImpl(); }
        protected:
            virtual bool IsKeyPressedImpl(int key) = 0;
            virtual bool IsMousePressedImpl(int btn) = 0; 
            virtual float GetMouseXImpl() = 0;
            virtual float GetMouseYImpl() = 0;
            virtual MousePos GetMousePosImpl() = 0;
        private:
            static Controls* s_Instance;
	};
}
