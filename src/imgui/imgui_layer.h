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
            
            virtual void OnAttach() override;
            virtual void OnDetach() override;
            virtual void OnImGuiRender() override; 

            void Begin();
            void End();
        private:
            float m_Time = 0.0f;
    };
}
