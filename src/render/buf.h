#pragma once

#include <stdint.h>
#include <vector>
#include <glad/glad.h>
#include "logging.h"

namespace RetroEngine {
    enum class GLSLType {
        Vec1 = 0,
        Vec2,
        Vec3,
        Vec4,
        Mat3,
        Mat4,
        IntVec1,
        IntVec2,
        IntVec3,
        IntVec4,
        Bool
    };
    static uint32_t SizeOfGLSLType(GLSLType type) {
        switch (type) {
            case GLSLType::Vec1:
                return 4;
            case GLSLType::Vec2:
                return 4 * 2;
            case GLSLType::Vec3:
                return 4 * 3;
            case GLSLType::Vec4:
                return 4 * 4;
            case GLSLType::Mat3:
                return 4 * 3 * 3;
            case GLSLType::Mat4:
                return 4 * 4 * 4;
            case GLSLType::IntVec1:
                return 4;
            case GLSLType::IntVec2:
                return 4 * 2;
            case GLSLType::IntVec3:
                return 4 * 3;
            case GLSLType::IntVec4:
                return 4 * 4;
            case GLSLType::Bool:
                return 1;
        }
        RET_CORE_FATAL("Unknown GLSL type");
        return 0;
    }
    struct BufElement {
        GLSLType type;
        char* name;
        uint32_t offset;
        uint32_t size;
        bool normalized;
        BufElement() {}
        BufElement(GLSLType type, char* name, bool normalized = false) : name(name), type(type), size(SizeOfGLSLType(type)), offset(0), normalized(normalized) {
        }
        uint32_t GetComponentCount() const {
            switch (type) {
                case GLSLType::Vec1: return 1;
                case GLSLType::Vec2: return 2;
                case GLSLType::Vec3: return 3;
                case GLSLType::Vec4: return 4;
                case GLSLType::IntVec1: return 1;
                case GLSLType::IntVec2: return 2;
                case GLSLType::IntVec3: return 3;
                case GLSLType::IntVec4: return 4;
                case GLSLType::Mat3: return 3 * 3;
                case GLSLType::Mat4: return 4 * 4;
                case GLSLType::Bool: return 1;
            }
        }
        inline const bool IsNormalized() const { return normalized; }
        GLenum GetBaseType() const {
            switch (type) {
                case GLSLType::Vec1:
                    return GL_FLOAT;
                case GLSLType::Vec2:
                    return GL_FLOAT;
                case GLSLType::Vec3:
                    return GL_FLOAT;
                case GLSLType::Vec4:
                    return GL_FLOAT;
                case GLSLType::Mat3:
                    return GL_FLOAT;
                case GLSLType::Mat4:
                    return GL_FLOAT;
                case GLSLType::IntVec1:
                    return GL_INT;
                case GLSLType::IntVec2:
                    return GL_INT;
                case GLSLType::IntVec3:
                    return GL_INT;
                case GLSLType::IntVec4:
                    return GL_INT;
                case GLSLType::Bool:
                    return GL_BOOL;
            }
            RET_CORE_FATAL("The GLSL type you specified is a sussy baka");
        };
    };
    class BufLayout {
    public:
        BufLayout() {}
        BufLayout(const std::initializer_list<BufElement>& e) : m_Elements(e) {
            uint32_t offset;
            m_Stride = 0;
            for (BufElement element : e) {
                element.offset = offset;
                offset += element.size;
                m_Stride += element.size;
            } 
        }
        inline const std::vector<BufElement>& GetElements() const { return m_Elements; }
        inline const uint32_t GetStride() const { return m_Stride; }
        std::vector<BufElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<BufElement>::iterator end() { return m_Elements.end(); };
    private:
        std::vector<BufElement> m_Elements;
        uint32_t m_Stride = 0;
    };
    class VertexBuf {
    public:
        virtual ~VertexBuf() {}
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void SetLayout(const BufLayout& layout) = 0;
        virtual const BufLayout& GetLayout() const = 0;
        static VertexBuf* Create(float vert[], uint32_t size);
    };
    class IndexBuf {
    public:
        virtual ~IndexBuf() {}
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual uint32_t GetCount() const = 0;
        static IndexBuf* Create(uint32_t indices[], uint32_t count);
    };
}
