#include "opengl_render_api.h"
#include <glad/glad.h>

namespace RetroEngine {
	void OpenGLRenderAPI::ClearCol(const glm::vec4& col) {
     	glClearColor(col.r, col.g, col.b, col.a);     
	}
	void OpenGLRenderAPI::Clear() {
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      
	}
	void OpenGLRenderAPI::DrawIndexed(const std::shared_ptr<VertexArray>& array) {
    	glDrawElements(GL_TRIANGLES, array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);      
	}
}