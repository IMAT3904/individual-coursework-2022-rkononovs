/** \file Renderer2D.h */
#pragma once

#include "rendering/RendererCommon.h"
#include "rendering/subTexture.h"
#include "rendering/textureAtlas.h"
#include "ft2build.h"
#include "freetype/freetype.h"

namespace Engine {
	class Renderer2DVertex {
	public:
		Renderer2DVertex() = default;
		Renderer2DVertex(const glm::vec4& pos, const glm::vec2& uv, uint32_t tu, const glm::vec4& pTint) : 
			position(pos), uvCoords(uv), texUnit(tu), tint(pack(pTint)) {};
		glm::vec4 position;
		glm::vec2 uvCoords;
		uint32_t texUnit;
		uint32_t tint;
		static VertexBufferLayout layout;
		static uint32_t pack(const glm::vec4& tint);
	};

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
			std::shared_ptr<OpenGLTexture> fontTexture;
			std::shared_ptr<OpenGLShader> shader;
			std::shared_ptr<OpenGLVertexArray> VAO;
			std::shared_ptr<OpenGLUniformBuffer> quadUBO;
			std::shared_ptr<unsigned char> glyphBuffer;
			std::shared_ptr <SubTexture> defaultSubTexture;
			std::array<glm::vec4, 4> quad;
			std::array<int32_t, 32> textureUnits;
			std::vector<Renderer2DVertex> vertices;
			static const uint32_t batchSize = 8192;
			glm::ivec2 glyphBufferDims;
			glm::vec4 defaultTint;
			glm::mat4 model;
			FT_Library ft;
			FT_Face font;
			uint32_t drawCount;
			uint32_t glyphBufferSize;
			TextureAtlas glyphAtlas;
		};

		static void RtoRGBA(unsigned char* rBuffer, uint32_t width, uint32_t height);
		static std::shared_ptr<InternalData> s_data;
	public:
		static void init(); //!< Init the renderer
		static void begin(const SceneWideUniforms& sceneWideUniforms); //!< Begin a new 2D scene
		static void submit(const Quad& quad, const glm::vec4& tint); //!< Render a tinted quad
		static void submit(const Quad& quad, const std::shared_ptr<SubTexture>& texture); //!< Render a textured quad
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<SubTexture>& texture); //!< Render a textured and tinted quad
		static void submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees = false); //!< Render a tinted quad with rotation
		static void submit(const Quad& quad, const std::shared_ptr<SubTexture>& texture, float angle, bool degrees = false); //!< Render a textured with rotation
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<SubTexture>& texture, float angle, bool degrees = false); //!< Render a textured and tinted quad with rotation

		static void submit(char ch, const glm::vec2& position, float& advance, const glm::vec4& tint); //!< Render a single character with a tint
		static void submit(const char * text, const glm::vec2& position, const glm::vec4& tint); //!< Render a line of character with a tint
		static void end(); //!< End the current 2D scene
		static void flush(); //!< 
	};
}