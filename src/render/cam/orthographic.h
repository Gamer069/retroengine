#pragma once

#include <glm/glm.hpp>

namespace RetroEngine {
	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		void SetPos(const glm::vec3 pos) { m_Pos = pos; RecalcView(); }
		void SetRotationZ(const float rotationZ) { m_RotationZ = rotationZ; RecalcView(); }
		const glm::vec3& GetPos() const { return m_Pos; }
		float GetRotationZ() const { return m_RotationZ; }
		const glm::mat4& GetProj() const { return m_Proj; }
		const glm::mat4& GetView() const { return m_View; }
		const glm::mat4& GetPV() const { return m_PV; }
	private:
		void RecalcView();
	private:
		glm::mat4 m_Proj;
		glm::mat4 m_View;
		glm::mat4 m_PV;
		glm::vec3 m_Pos;
		float m_RotationZ = 0.0f;
	};
}