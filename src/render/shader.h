#pragma once

#include "ret_pch.h"
#include <glm/glm.hpp>

namespace RetroEngine {
	class Shader {
	public:
		Shader(const std::string& vert, const std::string& frag);
		~Shader();

		void Bind() const;
		void Unbind() const;
		void UploadUniformMat4(const glm::mat4& mat, const char* name);
	private:
		uint32_t m_ShaderID;
	};
}