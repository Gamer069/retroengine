#pragma once

#include "render/array.h"
#include <stdint.h>

namespace RetroEngine {
	class OpenGLVertexArray : public VertexArray {
	public:
    	OpenGLVertexArray();
        ~OpenGLVertexArray();
        virtual void Bind() override;
        const uint32_t GetID() const override;
        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuf>& vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuf>& indexBuffer) override;
        virtual const std::vector<std::shared_ptr<VertexBuf>>& GetVertexBuffers() const override;
        virtual const std::shared_ptr<IndexBuf>& GetIndexBuffer() const override;
	private:
		uint32_t m_ArrayID;
		mutable std::vector<std::shared_ptr<VertexBuf>> m_VertexBuffers;
		std::shared_ptr<IndexBuf> m_IndexBuffer;
	};
}
