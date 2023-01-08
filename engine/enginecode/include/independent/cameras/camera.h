/* \file camera.h */
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "include/independent/events/events.h"

namespace Engine {
	/** \class Camera
		\brief Basic Camera base class
	*/
	class Camera {
	public:
		glm::mat4 view; //!< View matrix of the camera
		glm::mat4 projection = glm::perspective(glm::radians(45.f), 1024.f / 800.f, 0.1f, 100.f);; //!< Projection matrix of the camera
		void updateView(const glm::mat4& transform) { //!< Update the view matrix as an inverse of a model matrix
			view = glm::inverse(transform);
		}

	};
	/** \class CameraController
		\brief Basic Camera Controller base class
	*/
	class CameraController {
	protected:
		Camera m_camera; //!< Camera being controlled
	public:
		Camera& getCamera() { return m_camera; } //!< Getter for camera
		virtual void onUpdate(float t) {}; //!< Can update the camera
		virtual void onResize(WindowResizeEvent& e) {}; //!< Can handle events
	};
};