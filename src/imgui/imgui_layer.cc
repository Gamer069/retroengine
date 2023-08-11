#include "event/app_event.h"
#include "event/event.h"
#include "event/key_event.h"
#include "event/mouse_event.h"
#include "logging.h"
#define GLFW_INCLUDE_NONE
#include "imgui_layer.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "ret_pch.h"
#include "imgui_renderer.h"
#include "app.h"

#include <cmath>

namespace RetroEngine {
    #define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)
    ImGuiLayer::ImGuiLayer() : Layer("ImGui") {
    }
    ImGuiLayer::~ImGuiLayer() {
    }
    
    void ImGuiLayer::OnUpdate() {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
        
        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    
    void ImGuiLayer::OnAttach() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
    
        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors; 
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    
    
        // TODO: make code good
        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
    
        ImGui_ImplOpenGL3_Init("#version 410");
    }
    
    void ImGuiLayer::OnDetach() {
           
    }
    
    void ImGuiLayer::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);
        
        dispatcher.Dispatch<MouseMovedEvent>(BIND_FN(ImGuiLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MousePressEvent>(BIND_FN(ImGuiLayer::OnMousePressedEvent));
        dispatcher.Dispatch<MouseReleaseEvent>(BIND_FN(ImGuiLayer::OnMouseReleasedEvent));
        dispatcher.Dispatch<MouseScrollEvent>(BIND_FN(ImGuiLayer::OnMouseScrollEvent));
        dispatcher.Dispatch<KeyTypedEvent>(BIND_FN(ImGuiLayer::OnKeyTypedEvent));
        dispatcher.Dispatch<KeyPressedEvent>(BIND_FN(ImGuiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(BIND_FN(ImGuiLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<WinResizeEvent>(BIND_FN(ImGuiLayer::OnWindowResizedEvent));
    }
    
    bool ImGuiLayer::OnMousePressedEvent(MouseButtonEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetButton()] = true;
        return false;
    }
    bool ImGuiLayer::OnMouseReleasedEvent(MouseReleaseEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetButton()] = false;
        return false;
    }
    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e) {
        // Convert the mouse position to ImGui coordinate system
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(), e.GetY());
    
        return false;
    }
    
    
    
    bool ImGuiLayer::OnMouseScrollEvent(MouseScrollEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += e.GetXOffset();
        io.MouseWheel += e.GetYOffset();
        return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeycode()] = true;
        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
        return false;
    }
    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e) {
        RET_CORE_WARN("{0}", e);
        ImGuiIO& io = ImGui::GetIO();
        int keycode = e.GetKeycode();
        if (keycode > 0 && keycode < 0x10000)
          io.AddInputCharacter(static_cast<unsigned int>(keycode));

        return false;
    }
    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeycode()] = false;
      
        return false;
    }

    bool ImGuiLayer::OnWindowResizedEvent(WinResizeEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, e.GetWidth(), e.GetHeight());
    
        return false;
    }
}
