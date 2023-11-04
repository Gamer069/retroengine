#include "ret_pch.h"
#include "opengl_buf.h"

#include <glad/glad.h>

namespace RetroEngine {
    // VertexBuf //
    OpenGLVertexBuf::OpenGLVertexBuf(float vert[], uint32_t size) {
        glGenBuffers(1, &m_BufID);
        glBindBuffer(GL_ARRAY_BUFFER, m_BufID);
        glBufferData(GL_ARRAY_BUFFER, size, vert, GL_STATIC_DRAW);
    }
    OpenGLVertexBuf::~OpenGLVertexBuf() {
        glDeleteBuffers(1, &m_BufID);
    }
    void OpenGLVertexBuf::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufID);
    }
    void OpenGLVertexBuf::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    // IndexBuf //
    
    OpenGLIndexBuf::OpenGLIndexBuf(uint32_t indices[], uint32_t count) : m_Count(count) {
        glGenBuffers(1, &m_BufID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufID); 
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }
    OpenGLIndexBuf::~OpenGLIndexBuf() {
        glDeleteBuffers(1, &m_BufID);
    }
    void OpenGLIndexBuf::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufID);
    }
    void OpenGLIndexBuf::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
