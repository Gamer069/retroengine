#include "renderer.h"
#include "ret_pch.h"
#include "render_utils.h"

namespace RetroEngine {
    Renderer::Data* Renderer::s_Data = new Renderer::Data; 
    void Renderer::BeginScene(OrthographicCamera& cam) {
        s_Data->PV = cam.GetPV();
    }
    void Renderer::EndScene() {
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& array, const Transform& transform) {
        shader->Bind();
        shader->UploadUniformMat4(s_Data->PV, (const char*)"u_PV");
        shader->UploadUniformMat4(transform, (const char*)"u_Transform");
        array->Bind();
        RenderUtils::DrawIndexed(array);
    }
}
