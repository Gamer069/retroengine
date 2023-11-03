#include "ret_pch.h"
#include "inp.h"
#include "pinp.h"
#include "app.h"
#include <GLFW/glfw3.h>

namespace RetroEngine {
    Controls* Controls::s_Instance = new WindowsControls();
    bool WindowsControls::IsKeyPressedImpl(int key) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNative()); 
        auto state = glfwGetKey(window, key);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
    bool WindowsControls::IsMousePressedImpl(int btn) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNative()); 
        auto state = glfwGetMouseButton(window, btn);
        return state == GLFW_PRESS;
    }

    MousePos WindowsControls::GetMousePosImpl() {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNative()); 
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return { x, y };
    }

    float WindowsControls::GetMouseXImpl() {
        auto[x, y] = GetMousePosImpl();
        return x;
    }
    float WindowsControls::GetMouseYImpl() {
        auto[x, y] = GetMousePosImpl();
        return y;
    }
}
