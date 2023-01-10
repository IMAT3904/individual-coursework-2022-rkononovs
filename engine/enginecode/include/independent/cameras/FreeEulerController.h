/* \file FreeEulerController.h */
#pragma once
#include "camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "include/independent/core/inputPoller.h"
#include <algorithm>

namespace Engine {
	/** \struct EulerCameraProps
	*\brief common properties for Euler Camera defined when creating a Euler Camera
	\param position vec3 - position of the camera
	\param yaw float - Yaw for the mouse movement
	\param pitch float - Pitch for the mouse movement
	\param translationSpeed float - Movement speed of the camera
	\param rotationSpeed float - Rotation speed of the camera
	\param fovY float - FOV of camera
	\param aspectRation float - Aspect ratio of the camera
	\param nearClip float - How near object is to clip it
	\param farClip float - How far object has to be to clip it
	*/
	struct EulerCameraProps {
		glm::vec3 position = glm::vec3(0.f); //!< The position of the camera
		float yaw = 0.f; //!< The yaw for the mouse movement
		float pitch = 0.f; //!< The pitch for mouse movement
		float translationSpeed = 20.f; //!< The speed of camera
		float rotationSpeed = 2.0f; //!< The rotation speed of camera
		float fovY = 45.f; //!< default FOV
		float aspectRation = 16.f / 9.f; //!< Default aspect ration of camera
		float nearClip = 0.1f; //!< The near clip of camera
		float farClip = 100.f; //!< The far clip of camera
	};
	/**
	\class FreeEulerControllerEuler
	*\brief Class to make camera that moves in space
	*/
	class FreeEulerControllerEuler : public CameraController{
	private:
		EulerCameraProps m_props; //!< Camera Properties
		glm::mat4 m_model; //!< The imaginary model of camera
		glm::vec3 m_forward; //!< Forward and backwards vector
		glm::vec3 m_up; //!< Up and down vector
		glm::vec3 m_right; //!< Right and left vector
		glm::vec2 m_lastMousePosition; //!< Last mouse position
	public:
		FreeEulerControllerEuler(const EulerCameraProps& props); //!< Constructor
		void onUpdate(float timestep) override; //!< Update function
	};
}