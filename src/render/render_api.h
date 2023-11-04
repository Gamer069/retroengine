#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "array.h"
#include "render_context.h"
#include "ret_pch.h"

namespace RetroEngine {
	class RenderAPI {
	public:
		enum class API {
			None = 0,
			OpenGL = 1,
			DirectX = 2,
			Vulkan = 3,
		};
	public:
          virtual void ClearCol(const glm::vec4& col) = 0;
          virtual void Clear() = 0;
          virtual void DrawIndexed(const std::shared_ptr<VertexArray>& array) = 0;
          INLINE static API GetAPI() { return s_API; }
	private:
          static API s_API;
	};
}
