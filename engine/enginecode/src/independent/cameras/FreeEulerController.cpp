/** \file FreeEulerController.cpp */
#include "engine_pch.h"
#include "cameras/FreeEulerController.h"

namespace Engine {
	FreeEulerControllerEuler::FreeEulerControllerEuler(const EulerCameraProps& props) {
		m_props.position = props.position;
		m_props.yaw = props.yaw;
		m_props.pitch = props.pitch;
		m_props.translationSpeed = props.translationSpeed;
		m_props.rotationSpeed = props.rotationSpeed;
		m_props.fovY = props.fovY;
		m_props.aspectRation = props.aspectRation;
		m_props.nearClip = props.nearClip;
		m_props.farClip = props.farClip;

		glm::mat4 rotX = glm::rotate(glm::mat4(1.f), m_props.pitch, glm::vec3(1.f, 0.f, 0.f));
		glm::mat4 rotY = glm::rotate(glm::mat4(1.f), m_props.yaw, glm::vec3(0.f, 1.f, 0.f));
		m_model = glm::translate(glm::mat4(1.f), m_props.position) * (rotX * rotY);

		//Update the camera
		m_camera.updateView(m_model);

		//Update component vectors
		m_forward = { -m_model[2][0], -m_model[2][1], -m_model[2][2] };
		m_up = { m_model[1][0], m_model[1][1], m_model[1][2] };
		m_right = { m_model[0][0], m_model[0][1], m_model[0][2] };
	}
	void FreeEulerControllerEuler::onUpdate(float timestep){
		bool camMoved = false;
		if (InputPoller::isKeyPressed(NG_KEY_W)) {
			float y = m_props.position.y;
			m_props.position += m_forward * m_props.translationSpeed * timestep;
			m_props.position.y = y;
			camMoved = true;
		}
		if (InputPoller::isKeyPressed(NG_KEY_S)) {
			float y = m_props.position.y;
			m_props.position -= m_forward * m_props.translationSpeed * timestep;
			m_props.position.y = y;
			camMoved = true;
		}
		if (InputPoller::isKeyPressed(NG_KEY_A)) {
			m_props.position -= m_right * m_props.translationSpeed * timestep;
			camMoved = true;
		}
		if (InputPoller::isKeyPressed(NG_KEY_D)) {
			m_props.position += m_right * m_props.translationSpeed * timestep;
			camMoved = true;
		}
		if (InputPoller::isKeyPressed(NG_KEY_SPACE))
		{
			m_props.position += m_up * m_props.translationSpeed * timestep;
			camMoved = true;
		}
		if (InputPoller::isKeyPressed(NG_KEY_C))
		{
			m_props.position -= m_up * m_props.translationSpeed * timestep;
			camMoved = true;
		}
		if (InputPoller::isMouseButtonPressed(NG_MOUSE_BUTTON_RIGHT)) {
			if (m_lastMousePosition.x >= 0.f) {
				camMoved = true;
				glm::vec2 currentMousePosition = InputPoller::getMousePosition();
				glm::vec2 mouseDelta = currentMousePosition - m_lastMousePosition;

				m_props.yaw -= mouseDelta.x * m_props.rotationSpeed * timestep;
				m_props.pitch -= mouseDelta.y * m_props.rotationSpeed * timestep;

				m_props.pitch = std::clamp(m_props.pitch, -89.f, 89.f);
			}
			m_lastMousePosition = InputPoller::getMousePosition();
		}
		else {
			m_lastMousePosition.x = -1.f;
		}
		if (camMoved) {
			// Set model
			glm::mat4 rotX = glm::rotate(glm::mat4(1.f), m_props.pitch, glm::vec3(1.f, 0.f, 0.f));
			glm::mat4 rotY = glm::rotate(glm::mat4(1.f), m_props.yaw, glm::vec3(0.f, 1.f, 0.f));
			m_model = glm::translate(glm::mat4(1.f), m_props.position) * (rotX * rotY);

			//Update the camera
			m_camera.updateView(m_model);

			//Update component vectors
			m_forward = { -m_model[2][0], -m_model[2][1], -m_model[2][2] };
			m_up = { m_model[1][0], m_model[1][1], m_model[1][2] };
			m_right = { m_model[0][0], m_model[0][1], m_model[0][2] };
		}
	}
}