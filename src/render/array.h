#pragma once

#include <stdint.h>
#include <memory>
#include "buf.h"

namespace RetroEngine {
    class VertexArray {
    public:
        static VertexArray* Create();
        virtual void Bind() = 0;
        virtual const uint32_t GetID() const = 0;
        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuf>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuf>& indexBuffer) = 0;
        virtual const std::vector<std::shared_ptr<VertexBuf>>& GetVertexBuffers() const = 0;
        virtual const std::shared_ptr<IndexBuf>& GetIndexBuffer() const = 0;
    };
}
