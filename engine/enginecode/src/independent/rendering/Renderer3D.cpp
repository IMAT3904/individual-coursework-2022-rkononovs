/** \file Renderer3D.cpp */
#include "engine_pch.h"
#include "glad/glad.h"
#include "rendering/Renderer3D.h"

#include <glm/gtc/type_ptr.hpp>


namespace Engine{

	std::shared_ptr<Renderer3D::InternalData> Renderer3D::s_data = nullptr;
	TextureUnitManager Renderer3D::m_textureUnitManager = TextureUnitManager(32);
	uint32_t textSlot;

	void Renderer3D::init(){
		s_data.reset(new InternalData);

		unsigned char whitePx[4] = { 255, 255, 255, 255 };
		s_data->defaultTexture.reset(new OpenGLTexture(1, 1, 4, whitePx, 0));
		s_data->defaultTint = { 1.f, 1.f, 1.f, 1.f };

		UniformBufferLayout camLayout = { { "u_projection", ShaderDataType::Mat4}, {"u_view", ShaderDataType::Mat4} };
		s_data->cameraUBO.reset(new OpenGLUniformBuffer(camLayout));

		UniformBufferLayout lightLayout = { {"u_lightPos",ShaderDataType::Float3},{"u_viewPos",ShaderDataType::Float3}, {"u_lightColour",ShaderDataType::Float3} };
		s_data->lightUBO.reset(new OpenGLUniformBuffer(lightLayout));

		s_data->lightUBO->uploadData("u_lightPos", glm::value_ptr(s_data->lightPos));
		s_data->lightUBO->uploadData("u_viewPos", glm::value_ptr(s_data->viewPos));
		s_data->lightUBO->uploadData("u_lightColour", glm::value_ptr(s_data->lightColour));
	}
	void Renderer3D::begin(const SceneWideUniforms& sceneWideUniforms){
		glBindBuffer(GL_UNIFORM_BUFFER, s_data->cameraUBO->getRenderID());
		s_data->sceneWideUniforms = sceneWideUniforms;
		s_data->cameraUBO->uploadData("u_projection", sceneWideUniforms.at("u_projection").second);
		s_data->cameraUBO->uploadData("u_view", sceneWideUniforms.at("u_view").second);

		glBindBuffer(GL_UNIFORM_BUFFER, s_data->lightUBO->getRenderID());
		s_data->lightUBO->uploadData("u_viewPos", glm::value_ptr(s_data->viewPos));
	}
	void Renderer3D::submit(const std::shared_ptr<OpenGLVertexArray> geometry, const std::shared_ptr<Material>& material, const glm::mat4& model){
		//Bind shader
		glUseProgram(material->getShader()->getRenderID());
		glBindVertexArray(geometry->getRenderID());

		//Apply sceneWideUniforms
		for (auto& dataPair : s_data->sceneWideUniforms) {
			const char* nameOfUniform = dataPair.first;
			ShaderDataType& sdt = dataPair.second.first;
			void* addressOfValue = dataPair.second.second;

			switch (sdt) {
			case ShaderDataType::Int:
				material->getShader()->uploadInt(nameOfUniform, *(int*)addressOfValue);
				break;
			case ShaderDataType::Float3:
				material->getShader()->uploadFloat3(nameOfUniform, *(glm::vec3*)addressOfValue);
				break;
			case ShaderDataType::Float4:
				material->getShader()->uploadFloat3(nameOfUniform , *(glm::vec4*)addressOfValue);
				break;
			case ShaderDataType::Mat4:
				material->getShader()->uploadMat4(nameOfUniform, *(glm::mat4*)addressOfValue);
				break;
			}

		}

		//Apply material uniforms ( Per draw uniforms )
		material->getShader()->uploadMat4("u_model", model);

		std::shared_ptr<OpenGLTexture> texture;
		if (material->isFlagSet(Material::flag_texture)) {
			texture = material->getTexture();
		}
		else {
			texture = s_data->defaultTexture;
		}

		if (m_textureUnitManager.getUnit(texture->getRenderID(), textSlot)) {
			texture->bindToSlot(textSlot);
		}

		material->getShader()->uploadInt("u_texData", textSlot);

		if (material->isFlagSet(Material::flag_tint)) material->getShader()->uploadFloat4("u_tint", material->getTint());
		else material->getShader()->uploadFloat4("u_tint", s_data->defaultTint);

		//Bind the geometry (VAO and IBO)
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->getIndexBuffer()->getRenderID());

		//Submit the draw call
		glDrawElements(GL_TRIANGLES, geometry->getDrawnCount(), GL_UNSIGNED_INT, nullptr);
	}
	void Renderer3D::end(){
		s_data->sceneWideUniforms.clear();
	}
	void Renderer3D::attachShader(std::shared_ptr<OpenGLShader>& shader){
		//s_data->cameraUBO->attachShaderBlock(shader, "b_camera");
		s_data->lightUBO->attachShaderBlock(shader, "b_lights");
	}
}