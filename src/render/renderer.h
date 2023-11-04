#pragma once

#include "array.h"
#include "cam/orthographic.h"
#include "render/shader.h"
#include "render_api.h"
#include <memory>

typedef glm::mat4 Transform;
namespace RetroEngine {
	class Renderer {
		public:
            static void BeginScene(OrthographicCamera& cam);
            static void EndScene();
            static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& array, const Transform& transform = glm::mat4(1.0f));
			INLINE static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
		private:
			struct Data {
            	glm::mat4 PV;              
			};
			static Data* s_Data;
	};
}
