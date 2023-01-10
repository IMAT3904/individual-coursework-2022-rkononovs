/* \file FollowCamera.h */
#pragma once
#include "camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "include/independent/core/inputPoller.h"
#include <algorithm>

namespace Engine {
	/** \struct FollowParams
	*\brief common properties for Follow Camera defined when creating a Follow Camera
	\param entityTransform mat4* - The entity which camera will follow
	\param fovY float - FOV of camera
	\param aspectRation float - Aspect ratio of the camera
	\param nearClip float - How near object is to clip it
	\param farClip float - How far object has to be to clip it
	\param offset vec3 - The offset that camera has from the entity
	*/
	struct FollowParams { //!< Camera parameters
		glm::mat4* entityTransform; //!< Entity which it will follow
		float fovY = 45.f; //!< default FOV
		float aspectRation = 16.f / 9.f; //!< Default aspect ration of camera
		float nearClip = 0.1f; //!< The near clip of camera
		float farClip = 100.f; //!< The far clip of camera
		glm::vec3 offset; //!< The offset from entity
	};
	/**
	\class FollowCamera
	*\brief Class to make camera that follows player (cube)
	*/
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