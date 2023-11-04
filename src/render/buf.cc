#include "opengl/opengl_buf.h"
#include "renderer.h"
#include "ret_pch.h"
#include "buf.h"

namespace RetroEngine {
    VertexBuf* VertexBuf::Create(float* vert, uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RenderAPI::API::None: {
                RET_CORE_FATAL("The renderer for the Render API \"None\" is currently not supported: use a different api before this one gets implemented");
                return nullptr;
            }
            case RenderAPI::API::OpenGL: {
                return new OpenGLVertexBuf(vert, size);
            };
            case RenderAPI::API::Vulkan: {
                RET_CORE_FATAL("The renderer for the Render API \"Vulkan\" is currently not supported: use a different api before this one gets implemented");
                return nullptr;
            };
            case RenderAPI::API::DirectX: {
                RET_CORE_FATAL("The renderer for the Render API \"DirectX\" is currently not supported: use a different api before this one gets implemented");
                return nullptr;
            };
        }
        RET_CORE_FATAL("SUS renderer API.");
        return nullptr;
    }
    IndexBuf* IndexBuf::Create(uint32_t* indices, uint32_t size) {
          switch (Renderer::GetAPI()) {
              case RenderAPI::API::None: {
                  RET_CORE_FATAL("The renderer for the Render API \"None\" is currently not supported: use a different api before this one gets implemented");
                  return nullptr;
              }
              case RenderAPI::API::OpenGL: {
                  return new OpenGLIndexBuf(indices, size);
              };
              case RenderAPI::API::Vulkan: {
                  RET_CORE_FATAL("The renderer for the Render API \"Vulkan\" is currently not supported: use a different api before this one gets implemented");
                  return nullptr;
              };
              case RenderAPI::API::DirectX: {
                  RET_CORE_FATAL("The renderer for the Render API \"DirectX\" is currently not supported: use a different api before this one gets implemented");
                  return nullptr;
              };
          }
          RET_CORE_FATAL("SUS renderer API.");
          return nullptr;
    }
}
