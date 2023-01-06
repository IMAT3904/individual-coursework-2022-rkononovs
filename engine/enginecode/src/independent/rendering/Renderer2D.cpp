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

		std::shared_ptr<OpenGLVertexBuffer> VBO;
		std::shared_ptr<OpenGLIndexBuffer> IBO;
		s_data->VAO.reset(new OpenGLVertexArray());
		VBO.reset(new OpenGLVertexBuffer(vertices, sizeof(vertices), VertexBufferLayout({ ShaderDataType::Float2, ShaderDataType::Float2 })));
		IBO.reset(new OpenGLIndexBuffer(indices, 4));
		s_data->VAO->addVertexBuffer(VBO);
		s_data->VAO->setIndexBuffer(IBO);
	}

	void Renderer2D::begin(const SceneWideUniforms& sceneWideUniforms){
		// Bind the shader
		glUseProgram(s_data->shader->getRenderID());

		//Apply sceneWideUniforms
		for (auto& dataPair : sceneWideUniforms) {
			const char* nameOfUniform = dataPair.first;
			ShaderDataType sdt = dataPair.second.first;
			void* addressOfValue = dataPair.second.second;

			switch (sdt) {
			case ShaderDataType::Int:
				s_data->shader->uploadInt(nameOfUniform, *(int*)addressOfValue);
				break;
			case ShaderDataType::Float3:
				s_data->shader->uploadFloat3(nameOfUniform, *(glm::vec3*)addressOfValue);
				break;
			case ShaderDataType::Float4:
				s_data->shader->uploadFloat3(nameOfUniform, *(glm::vec4*)addressOfValue);
				break;
			case ShaderDataType::Mat4:
				s_data->shader->uploadMat4(nameOfUniform, *(glm::mat4*)addressOfValue);
				break;
			}

			// Bind the geometry
			glBindVertexArray(s_data->VAO->getRenderID());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIndexBuffer()->getRenderID());
		}
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint){
		glBindTexture(GL_TEXTURE_2D, s_data->defaultTexture->getRenderID());
		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_scale), quad.m_translate);

		s_data->shader->uploadInt("u_texData", 0);
		s_data->shader->uploadFloat4("u_tint", tint);
		s_data->shader->uploadMat4("u_model", s_data->model);

		glDrawElements(GL_QUADS, s_data->VAO->getDrawnCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer2D::end(){
	}

	Quad Quad::createCentralHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents) {
		Quad result;

		result.m_translate = glm::vec3(centre, 0.f);
		result.m_scale = glm::vec3(halfExtents * 2.f, 1.f);

		return result;
	}
}