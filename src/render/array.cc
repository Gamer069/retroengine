#pragma once

#include "array.h"
#include "renderer.h"
#include "logging.h"
#include "opengl_array.h"

namespace RetroEngine {
	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI()) {
          	case RenderAPI::None: {
            	RET_CORE_FATAL("The renderer for the Render API \"None\" is currently not supported: use a different api before this one gets implemented");
            	return nullptr;
          	}
          	case RenderAPI::OpenGL: {
            	return new OpenGLVertexArray();
          	};
          	case RenderAPI::Vulkan: {
            	RET_CORE_FATAL("The renderer for the Render API \"Vulkan\" is currently not supported: use a different api before this one gets implemented");
            	return nullptr;
          	};
          	case RenderAPI::DirectX: {
            	RET_CORE_FATAL("The renderer for the Render API \"DirectX\" is currently not supported: use a different api before this one gets implemented");
            	return nullptr;
          	};
          }
          RET_CORE_FATAL("SUS renderer API.");
	}
}