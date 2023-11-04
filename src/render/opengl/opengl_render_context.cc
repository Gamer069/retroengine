#include "opengl_render_context.h"
#include "glad/glad.h"
#include "ret_pch.h"
#include <GLFW/glfw3.h>

namespace RetroEngine {
	OpenGLRenderContext::OpenGLRenderContext(GLFWwindow* win) : m_Window(win) {
		if (!win) {
			RET_CORE_FATAL("Failed to creaste OpenGL render context: window is undefined");		
		}	
	}
	void OpenGLRenderContext::Init() {
        glfwMakeContextCurrent(m_Window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (!status) RET_CORE_FATAL("Failed to initialize GLAD.");
	}
	void OpenGLRenderContext::SwapBuffers() {
		glfwSwapBuffers(m_Window);		
	}
}