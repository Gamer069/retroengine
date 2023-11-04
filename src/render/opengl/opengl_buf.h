#pragma once

#include "render/buf.h"

namespace RetroEngine {
    class OpenGLVertexBuf : public VertexBuf {
    public:
        OpenGLVertexBuf(float vert[], uint32_t size);
        virtual ~OpenGLVertexBuf();
        virtual void Bind() const override;
        virtual void Unbind() const override;
        inline virtual void SetLayout(const BufLayout& layout) override { m_Layout = layout; };
        inline virtual const BufLayout& GetLayout() const override { return m_Layout; };
    private:
        uint32_t m_BufID;
        BufLayout m_Layout;
    };
    class OpenGLIndexBuf : public IndexBuf {
    public:
        OpenGLIndexBuf(uint32_t indices[], uint32_t size);
        virtual ~OpenGLIndexBuf();
        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual uint32_t GetCount() const override { return m_Count; }
    private:
        uint32_t m_BufID;
        uint32_t m_Count;
    };
}
