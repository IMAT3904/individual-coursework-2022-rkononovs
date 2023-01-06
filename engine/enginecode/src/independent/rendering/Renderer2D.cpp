/* \file Renderer2D.cpp */
#include "engine_pch.h"
#include "rendering/Renderer2D.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
	std::shared_ptr<Renderer2D::InternalData> Renderer2D::s_data = nullptr;

	void Renderer2D::init(){
		s_data.reset(new InternalData);

		unsigned char whitePx[4] = { 255, 255, 255, 255 };
		s_data->defaultTexture.reset(new OpenGLTexture(1, 1, 4, whitePx, 0));
		s_data->defaultTint = { 1.f, 1.f, 1.f, 1.f };

		s_data->model = glm::mat4(1.0f);

		s_data->shader.reset(new OpenGLShader("./assets/shaders/quad1.glsl"));

		float vertices[4 * 4] = {
			-0.5f, -0.5f, 0.f, 0.f,
			-0.5f,  0.5f, 0.f, 1.f,
			 0.5f,  0.5f, 1.f, 1.f,
			 0.5,  -0.5f, 1.f, 0.f
		};

		uint32_t indices[4] = { 0,1,2,3 };

		UniformBufferLayout quadLayout = { { "u_projection", ShaderDataType::Mat4}, {"u_view", ShaderDataType::Mat4} };
		s_data->quadUBO.reset(new OpenGLUniformBuffer(quadLayout));

		std::shared_ptr<OpenGLVertexBuffer> VBO;
		std::shared_ptr<OpenGLIndexBuffer> IBO;

		s_data->VAO.reset(new OpenGLVertexArray());
		VBO.reset(new OpenGLVertexBuffer(vertices, sizeof(vertices), VertexBufferLayout({ ShaderDataType::Float2, ShaderDataType::Float2 })));
		IBO.reset(new OpenGLIndexBuffer(indices, 4));

		s_data->VAO->addVertexBuffer(VBO);
		s_data->VAO->setIndexBuffer(IBO);

		s_data->quadUBO->attachShaderBlock(s_data->shader, "b_cameraQuad");
	}

	void Renderer2D::begin(const SceneWideUniforms& sceneWideUniforms){
		// Bind the geometry
		glBindVertexArray(s_data->VAO->getRenderID());

		// Bind the shader
		glUseProgram(s_data->shader->getRenderID());
		
		
		s_data->quadUBO->uploadData("u_view", sceneWideUniforms.at("u_view").second);
		s_data->quadUBO->uploadData("u_projection", sceneWideUniforms.at("u_projection").second);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint){
		Renderer2D::submit(quad, tint, s_data->defaultTexture);
	}

	void Renderer2D::submit(const Quad& quad, const std::shared_ptr<OpenGLTexture>& texture){
		Renderer2D::submit(quad, s_data->defaultTint, texture);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<OpenGLTexture>& texture){

		uint32_t textSlot;
		const uint32_t& textureID = texture->getRenderID();
		bool needsBinding = RendererCommon::s_textureUnitManager.getUnit(textureID, textSlot);
		if (needsBinding) {
			if (textSlot == -1) {
				RendererCommon::s_textureUnitManager.clear();
				RendererCommon::s_textureUnitManager.getUnit(textureID, textSlot);
			}
			texture->bindToSlot(textSlot);
		}

		s_data->shader->uploadInt("u_texData", textSlot);

		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_translate), quad.m_scale);

		s_data->shader->uploadFloat4("u_tint", tint);
		s_data->shader->uploadMat4("u_model", s_data->model);

		glDrawElements(GL_QUADS, s_data->VAO->getDrawnCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees){
		Renderer2D::submit(quad, tint, s_data->defaultTexture, angle, degrees);
	}

	void Renderer2D::submit(const Quad& quad, const std::shared_ptr<OpenGLTexture>& texture, float angle, bool degrees){
		Renderer2D::submit(quad, s_data->defaultTint, texture, angle, degrees);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<OpenGLTexture>& texture, float angle, bool degrees)
	{
		if (degrees) angle = glm::radians(angle);

		uint32_t textSlot;
		const uint32_t& textureID = texture->getRenderID();
		bool needsBinding = RendererCommon::s_textureUnitManager.getUnit(textureID, textSlot);
		if (needsBinding) {
			if (textSlot == -1) {
				RendererCommon::s_textureUnitManager.clear();
				RendererCommon::s_textureUnitManager.getUnit(textureID, textSlot);
			}
			texture->bindToSlot(textSlot);
		}

		s_data->shader->uploadInt("u_texData", textSlot);

		s_data->model = glm::scale(glm::rotate(glm::translate(glm::mat4(1.f), quad.m_translate), angle, {0.f, 0.f, 1.f }), quad.m_scale);

		s_data->shader->uploadFloat4("u_tint", tint);
		s_data->shader->uploadMat4("u_model", s_data->model);

		glDrawElements(GL_QUADS, s_data->VAO->getDrawnCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer2D::end(){
	}

	Quad Quad::createCentralHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents) {
		Quad result;

		result.m_translate = glm::vec3(centre, 0.f);
		result.m_scale = glm::vec3(halfExtents * 2.0f, 1.0f);

		return result;
	}
}