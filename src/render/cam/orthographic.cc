#include "orthographic.h"
#include "ret_pch.h"

#include <glm/gtc/matrix_transform.hpp>

namespace RetroEngine {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : m_Proj(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_View(1.0f) {
		m_PV = m_Proj * m_View;
	}
	void OrthographicCamera::RecalcView() {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Pos) * glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationZ), glm::vec3(0, 0, 1));
		m_View = glm::inverse(transform);
		m_PV = m_Proj * m_View;
	}
}