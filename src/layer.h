#pragma once

#include "event/event.h"
#include "util/time.h"

namespace RetroEngine {
    class Layer {
        public:
            Layer(const std::string& name = "Layer");
            virtual ~Layer();
            
            virtual void OnAttach() {}
            virtual void OnDetach() {}
            virtual void OnUpdate(Time ts) {}
            virtual void OnImGuiRender() {}
            virtual void OnEvent(Event& event) {}
            
            inline const std::string& GetName() const { return m_Name; }
        protected:
            std::string m_Name;
    };
}
