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
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include "app.h"

#include <cmath>

namespace RetroEngine {
    #define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)
    ImGuiLayer::ImGuiLayer() : Layer("ImGui") {
    }
    ImGuiLayer::~ImGuiLayer() {
    }
    
    void ImGuiLayer::OnAttach() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application& app = Application::Get();
        GLFWwindow* win = static_cast<GLFWwindow*>(app.GetWindow().GetNative());
        io.BackendPlatformUserData = nullptr;
        ImGui_ImplGlfw_InitForOpenGL(win, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }
    
    void ImGuiLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::Begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
    void ImGuiLayer::End() {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup);
        }
    }
    void ImGuiLayer::OnImGuiRender() {
    }
}
