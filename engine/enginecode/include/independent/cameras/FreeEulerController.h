/* \file FreeEulerController.h */
#pragma once
#include "camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "include/independent/core/inputPoller.h"
#include <algorithm>

namespace Engine {
	struct EulerCameraProps {
		glm::vec3 position = glm::vec3(0.f);
		float yaw = 0.f;
		float pitch = 0.f;
		float translationSpeed = 20.f;
		float rotationSpeed = 2.0f;
		float fovY = 45.f;
		float aspectRation = 16.f / 9.f;
		float nearClip = 0.1;
		float farClip = 100.f;
	};

	class FreeEulerControllerEuler : public CameraController{
	private:
		EulerCameraProps m_props;
		glm::mat4 m_model;
		glm::vec3 m_forward;
		glm::vec3 m_up;
		glm::vec3 m_right;
		glm::vec2 m_lastMousePosition;
	public:
		FreeEulerControllerEuler(const EulerCameraProps& props);
		void onUpdate(float timestep) override;
	};
}