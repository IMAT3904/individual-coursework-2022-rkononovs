/** \file Renderer2D.h */
#pragma once

#include "rendering/RendererCommon.h"

namespace Engine {
	class Quad {
	private:
		glm::vec3 m_translate = glm::vec3(0.f); //!< Translation vector
		glm::vec3 m_scale = glm::vec3(1.f); //!< Scale vector
		friend class Renderer2D;
	public:
		Quad() = default;
		static Quad createCentralHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents);
	};

	/** \class Renderer2D
	** \brief Class which allows the rendering of simple 2D primitive
	*/
	class Renderer2D {
	private:
		struct InternalData {
			std::shared_ptr<OpenGLTexture> defaultTexture;
			std::shared_ptr<OpenGLShader> shader;
			std::shared_ptr<OpenGLVertexArray> VAO;
			std::shared_ptr<OpenGLUniformBuffer> quadUBO; 
			glm::vec4 defaultTint;
			glm::mat4 model;
		};

		static std::shared_ptr<InternalData> s_data;
		//static TextureUnitManager m_textureUnitManager;

	public:
		static void init(); //!< Init the renderer
		static void begin(const SceneWideUniforms& sceneWideUniforms); //!< Begin a new 2D scene
		static void submit(const Quad& quad, const glm::vec4& tint); //!< Render a tinted quad
		static void submit(const Quad& quad, const std::shared_ptr<OpenGLTexture>& texture); //!< Render a textured quad
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<OpenGLTexture>& texture); //!< Render a textured and tinted quad
		static void end(); //!< End the current 2D scene
	};
}