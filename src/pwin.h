#pragma once

#define GLFW_INCLUDE_NONE
#include "window.h"
#include "ret_pch.h"
#include "glfw/glfw3.h"

namespace RetroEngine {
    class WindowsWindow : public Window {
        public:
            WindowsWindow(const Win& properties);
            virtual ~WindowsWindow();
            
            void Update() override;
            static void GLFWErrorCallback(int error, const char* description);
            
            inline unsigned int GetWidth() const override { return m_Data.Width; }
            inline unsigned int GetHeight() const override { return m_Data.Height; }
            
            inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.callback = callback; }
            void SetVSync(bool vsync) override;
            bool IsVSync() const override;
        private:
            virtual void Init(const Win& properties);
            virtual void Shutdown();
        private:
            GLFWwindow* m_Window;
            
            struct WindowData {
                std::string Title;
                unsigned int Width;
                unsigned int Height;
                bool VSync;
                
                EventCallbackFn callback;
            };
            
            struct WindowData m_Data;
    };
}