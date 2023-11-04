#include "opengl_array.h"

#include <glad/glad.h>

namespace RetroEngine {
    OpenGLVertexArray::OpenGLVertexArray() {
        glGenVertexArrays(1, &m_ArrayID);
        glBindVertexArray(m_ArrayID);
	}
	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_ArrayID);
	}
	void OpenGLVertexArray::Bind() {
        glBindVertexArray(m_ArrayID);
	}
	const uint32_t OpenGLVertexArray::GetID() const {
		return m_ArrayID;
	}
    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuf>& buf) {
        if (!buf->GetLayout().GetElements().size()) {
            RET_CORE_FATAL("Vert Buf has no layout");
        }
        glBindVertexArray(m_ArrayID);
        buf->Bind();

        const auto& layout = buf->GetLayout();
        for (uint32_t i = 0; i < layout.GetElements().size(); i++) {
            const BufElement element = layout.GetElements()[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.GetComponentCount(), element.GetBaseType(), element.IsNormalized() ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.offset);
        }
        m_VertexBuffers.push_back(buf);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuf>& indexBuffer) {
        glBindVertexArray(m_ArrayID);
        indexBuffer->Bind();
        m_IndexBuffer = indexBuffer;
    }
    const std::shared_ptr<IndexBuf>& OpenGLVertexArray::GetIndexBuffer() const {
        return m_IndexBuffer;
    }
    const std::vector<std::shared_ptr<VertexBuf>>& OpenGLVertexArray::GetVertexBuffers() const {
        return m_VertexBuffers;
    }
}
