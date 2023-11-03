#pragma once

#include "render_context.h"

struct GLFWwindow;

namespace RetroEngine {
	class OpenGLRenderContext : public RenderContext {
	public:
		OpenGLRenderContext(GLFWwindow* win);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_Window;
	};
}