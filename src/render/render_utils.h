#pragma once

#include "render_context.h"
#include <glm/glm.hpp>
#include <memory>
#include "array.h"
#include "render_api.h"
#include "ret_pch.h"

namespace RetroEngine {
	class RenderUtils {
	public:
  		INLINE static void ClearCol(const glm::vec4& color) {
        	s_API->ClearCol(color);          
		}
  		INLINE static void Clear() {
        	s_API->Clear();        
		};
		INLINE static void DrawIndexed(const std::shared_ptr<VertexArray>& array) {
        	s_API->DrawIndexed(array);        
		};
	private:
  		static RenderAPI* s_API;
	};
}