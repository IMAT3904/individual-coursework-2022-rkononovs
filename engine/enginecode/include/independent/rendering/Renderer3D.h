/** \file Renderer3D.h */
#pragma once
#include "rendering/RendererCommon.h"

namespace Engine {

	/** \class Material/
	*   \brief Gold a shader and the uniform data associated with that shader
	*/
	class Material {
	private:
		uint32_t m_flags = 0; //!< Bitfield representation of the shader settings
		std::shared_ptr<OpenGLShader> m_shader; //!< The material shader
		std::shared_ptr<OpenGLTexture> m_texture; //!< The texture to be applied to the material
		glm::vec4 m_tint; //!< Colour tint ( Albedo ) to be applied to the geometry

		void setFlag(uint32_t flag) { m_flags = m_flags | flag; }
	public:
		Material(const std::shared_ptr<OpenGLShader>& shader) : m_shader(shader), m_flags(0), m_texture(nullptr), m_tint(glm::vec4(0.f)) {}
		Material(const std::shared_ptr<OpenGLShader>& shader, const std::shared_ptr<OpenGLTexture>& texture, const glm::vec4& tint) :
			m_shader(shader), m_texture(texture), m_tint(tint) {
			setFlag(flag_texture | flag_tint);
		}
		Material(const std::shared_ptr<OpenGLShader>& shader, const std::shared_ptr<OpenGLTexture>& texture) :
			m_shader(shader), m_texture(texture), m_tint(glm::vec4(0.f)) {
			setFlag(flag_texture);
		}
		Material(const std::shared_ptr<OpenGLShader>& shader, const glm::vec4& tint) :
			m_shader(shader), m_texture(nullptr), m_tint(tint) {
			setFlag(flag_tint);
		}

		inline std::shared_ptr<OpenGLShader> getShader() const { return m_shader; }
		inline std::shared_ptr<OpenGLTexture> getTexture() const { return m_texture; }
		inline glm::vec4 getTint() const { return m_tint; }
		bool isFlagSet(uint32_t flag) const { return m_flags & flag; }

		void setTexture(const std::shared_ptr<OpenGLTexture>& texture) { m_texture = texture; }
		void setTint(const glm::vec4& tint) { m_tint = tint; }

		constexpr static uint32_t flag_texture = 1 << 0;	//!< 00000001
		constexpr static uint32_t flag_tint = 1 << 1;		//!< 00000010
	};

	/** \class Renderer3D 
	** \brief A class which renders 3D geometry instantly
	*/
	class Renderer3D {
	private:
		struct InternalData {
			SceneWideUniforms sceneWideUniforms;
			uint32_t slot;
			std::shared_ptr<OpenGLUniformBuffer> cameraUBO; //!< Camera UBO data
			std::shared_ptr<OpenGLUniformBuffer> lightUBO; //!< Lights UBO data
			std::shared_ptr<OpenGLTexture> defaultTexture; //!< Empty white texture
			glm::vec4 defaultTint; //!< Default white tint
			glm::vec3 lightColour = glm::vec3(1.f, 1.f, 1.f);
			glm::vec3 lightPos = glm::vec3(1.f, 4.f, 6.f);
			glm::vec3 viewPos = glm::vec3(0.f, 0.f, 0.f);
		};
		//static TextureUnitManager m_textureUnitManager;
		static std::shared_ptr<InternalData> s_data; //!< Data internal to the renderer
	public:
		static void init(); //!< Init the renderer
		static void begin(const SceneWideUniforms& sceneWideUniforms); //!< Begin a new 3D scene
		static void submit(const std::shared_ptr<OpenGLVertexArray> geometry, const std::shared_ptr<Material>& material, const glm::mat4& model); //!< Submit a piece of geometry to be rendered
		static void end(); //!< End the current 3D scene
		static void attachShader(std::shared_ptr<OpenGLShader>& shader); //!< Attach shader ot the UBO's
	};
}