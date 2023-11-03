#pragma once

#include "ret_pch.h"

namespace RetroEngine {
	class Shader {
	public:
		Shader(const std::string& vert, const std::string& frag);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_ShaderID;
	};
}