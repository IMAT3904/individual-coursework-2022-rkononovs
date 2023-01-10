/** \file FollowCamera.cpp */
#include "engine_pch.h"
#include "cameras/FollowCamera.h"

namespace Engine{
	FollowCamera::FollowCamera(FollowParams& params){
		// Initialize every parameter
		m_params.entityTransform = params.entityTransform;
		m_params.fovY = params.fovY;
		m_params.aspectRation = params.aspectRation;
		m_params.nearClip = params.nearClip;
		m_params.farClip = params.farClip;
		m_params.offset = params.offset;
		
		// Calculate first position
		glm::vec3 right = { (*m_params.entityTransform)[0][0], (*m_params.entityTransform)[0][1], (*m_params.entityTransform)[0][2] };
		glm::vec3 up = { (*m_params.entityTransform)[1][0], (*m_params.entityTransform)[1][1], (*m_params.entityTransform)[1][2] };
		glm::vec3 forward = { -(*m_params.entityTransform)[2][0], -(*m_params.entityTransform)[2][1], -(*m_params.entityTransform)[2][2] };
		m_enityPosition = { (*m_params.entityTransform)[3][0], (*m_params.entityTransform)[3][1], (*m_params.entityTransform)[3][2] };

		glm::vec3 posDelta(0.f);
		posDelta += forward * -m_params.offset.z;
		posDelta += right * m_params.offset.x;
		posDelta += up * m_params.offset.y;

		m_position = m_enityPosition + posDelta;
		glm::vec3 camForward = -posDelta;
		glm::vec3 camRight = glm::cross({ 0,1, 0 }, posDelta);
		glm::vec3 camUp = glm::normalize(glm::cross(camRight, camForward));

		// Apply the position to camera
		m_camera.view = glm::lookAt(m_position, m_enityPosition, camUp);
	}
	void FollowCamera::onUpdate(float timestep){
		// Retrieve all movement vectors and calculate actual entity position
		glm::vec3 right = { (*m_params.entityTransform)[0][0], (*m_params.entityTransform)[0][1], (*m_params.entityTransform)[0][2] };
		glm::vec3 up = { (*m_params.entityTransform)[1][0], (*m_params.entityTransform)[1][1], (*m_params.entityTransform)[1][2] };
		glm::vec3 forward = { -(*m_params.entityTransform)[2][0], -(*m_params.entityTransform)[2][1], -(*m_params.entityTransform)[2][2] };
		m_enityPosition = { (*m_params.entityTransform)[3][0], (*m_params.entityTransform)[3][1], (*m_params.entityTransform)[3][2] };

		glm::vec3 posDelta(0.f);
		posDelta += forward * -m_params.offset.z;
		posDelta += right * m_params.offset.x;
		posDelta += up * m_params.offset.y;

		m_position = m_enityPosition + posDelta;
		glm::vec3 camForward = -posDelta;
		glm::vec3 camRight = glm::cross({ 0,1, 0 }, posDelta);
		glm::vec3 camUp = glm::normalize(glm::cross(camRight, camForward));

		// Apply the position to camera
		m_camera.view = glm::lookAt(m_position, m_enityPosition, camUp);
	}
}