#pragma once

#include <stdint.h>

namespace RetroEngine {
	class VertexArray {
	public:
    	static VertexArray* Create();
        virtual void Bind() = 0;
        virtual const uint32_t GetID() const = 0;
	};
}