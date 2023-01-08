/* \file FollowCamera.h */
#pragma once
#include "camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "include/independent/core/inputPoller.h"
#include <algorithm>

namespace Engine {
	struct FollowParams {
		glm::mat4* entityTransform;
		float fovY = 45.f;
		float aspectRation = 16.f / 9.f;
		float nearClip = 0.1f;
		float farClip = 100.f;
		glm::vec3 offset;
	};
	class FollowCamera : public CameraController {
	private:
		FollowParams m_params; //!< Parameters of camera
		glm::vec3 m_enityPosition; //!< Enities position
		glm::vec3 m_position; //!< Camera position
	public:
		FollowCamera(FollowParams& params); //!< Constructor
		virtual void onUpdate(float timestep) override; //!< Update function
	};
}