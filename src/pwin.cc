#include "glad/glad.h"
#include "pwin.h"
#include "event/app_event.h"
#include "event/mouse_event.h"
#include "event/key_event.h"
#include "logging.h"

namespace RetroEngine {
    static bool s_Initialized = false;
    
    Window* Window::Create(const Win& properties) {
        return new WindowsWindow(properties);
    }
    
    WindowsWindow::WindowsWindow(const Win& properties) {
        Init(properties);
    }
    
    WindowsWindow::~WindowsWindow() {
        Shutdown();
    }
    
    void WindowsWindow::GLFWErrorCallback(int error, const char* description) {
        RET_CORE_ERROR("GLFW ERROR: ({0}), description: {1}", error, description); 
    }
    
    void WindowsWindow::Init(const Win& properties) {
        m_Data.Title = properties.Title;
        m_Data.Width = properties.Width;
        m_Data.Height = properties.Height;
        
        RET_CORE_INFO("Creating window '{0}', {1}, {2}", properties.Title, properties.Width, properties.Height);
        
        if (!s_Initialized) {
            int suc = glfwInit();
            if (!suc) {
                RET_CORE_FATAL("Failed to init GLFW.");
                glfwSetErrorCallback(WindowsWindow::GLFWErrorCallback);
            }
            
            s_Initialized = true;
        }
        #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
        m_Window = glfwCreateWindow((int)properties.Width, (int)properties.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (!status) RET_CORE_FATAL("Failed to initialize GLAD.");
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(false);
        
        // GLFW callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* win, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(win);
            data.Width = width;
            data.Height = height;
            
            WinResizeEvent e(width, height);
            
            data.callback(e);
        });
        
        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* win) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(win);
            WinCloseEvent e;
            
            data.callback(e);
        });
        
        glfwSetKeyCallback(m_Window, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(win);
            
            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent e(key, 0);
                    
                    data.callback(e);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent e(key);
                  
                    data.callback(e);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent e(key, 1);
                  
                    data.callback(e);
                    break;
                }
            }
        });
        
        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* win, int btn, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(win);
            
            switch (action) {
                case GLFW_PRESS: {
                    MousePressEvent e(btn);
                    data.callback(e);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseReleaseEvent e(btn);
                    data.callback(e);
                    break;
                }
            }
        });
        
        glfwSetScrollCallback(m_Window, [](GLFWwindow* win, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(win);
            
            MouseScrollEvent e((float)xOffset, (float)yOffset);
            data.callback(e);
        });
        
        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* win, double x, double y) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(win);
            MouseMovedEvent e((float)x, (float)y);
            data.callback(e);
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* win, unsigned int keycode) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(win);
            KeyTypedEvent e(keycode);
            data.callback(e);
        });
    }
    
    void WindowsWindow::Shutdown() {
        glfwDestroyWindow(m_Window);
    }
    
    void WindowsWindow::Update() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }
    
    void WindowsWindow::SetVSync(bool vsync) {
        vsync ? glfwSwapInterval(1) : glfwSwapInterval(0);
        
        m_Data.VSync = vsync;
    }
    
    bool WindowsWindow::IsVSync() const {
        return m_Data.VSync;
    }
}