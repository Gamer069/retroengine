#pragma once

#include "array.h"
#include <stdint.h>

namespace RetroEngine {
	class OpenGLVertexArray : public VertexArray {
	public:
    	OpenGLVertexArray();
        virtual void Bind() override;
        const uint32_t GetID() const override;
	private:
		uint32_t m_ArrayID;
	};
}