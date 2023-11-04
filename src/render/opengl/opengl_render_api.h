#pragma once

#include "render/render_api.h"

namespace RetroEngine {
	class OpenGLRenderAPI : public RenderAPI {
           virtual void ClearCol(const glm::vec4& col) override;
           virtual void Clear() override;
           virtual void DrawIndexed(const std::shared_ptr<VertexArray>& array) override;          
	};
}