#include "opengl_array.h"

#include <glad/glad.h>

namespace RetroEngine {
	OpenGLVertexArray::OpenGLVertexArray() {
        glGenVertexArrays(1, &m_ArrayID);
        glBindVertexArray(m_ArrayID);
	}
	void OpenGLVertexArray::Bind() {
        glBindVertexArray(m_ArrayID);
	}
	const uint32_t OpenGLVertexArray::GetID() const {
		return m_ArrayID;
	}
}