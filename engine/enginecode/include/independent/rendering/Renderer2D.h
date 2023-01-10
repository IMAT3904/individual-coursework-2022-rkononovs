/** \file Renderer2D.h */
#pragma once

#include "rendering/RendererCommon.h"
#include "rendering/subTexture.h"
#include "rendering/textureAtlas.h"
#include "ft2build.h"
#include "freetype/freetype.h"

namespace Engine {
	/** \class VertexRenderer2D
	*\brief class to batch 2d rendering objects and text
	*/
	class Renderer2DVertex {
	public:
		Renderer2DVertex() = default; //!< Default constructor
		Renderer2DVertex(const glm::vec4& pos, const glm::vec2& uv, uint32_t tu, const glm::vec4& pTint) : 
			position(pos), uvCoords(uv), texUnit(tu), tint(pack(pTint)) {}; //!< Constructor with parameters
		glm::vec4 position; //!< Position of the quad
		glm::vec2 uvCoords; //!< UV coords of the quad
		uint32_t texUnit; //!< Texture unit
		uint32_t tint; //!< Tint ( Colour / Albedo ) for the quad
		static VertexBufferLayout layout; //!< Vertex buffer layout
		static uint32_t pack(const glm::vec4& tint); //!< Pack the tint
	};

	/** \class Quad
	*\brief class to render 2D quad
	*/
	class Quad {
	private:
		glm::vec3 m_translate = glm::vec3(0.f); //!< Translation vector
		glm::vec3 m_scale = glm::vec3(1.f); //!< Scale vector
		friend class Renderer2D; //!< Setting Renderer2D as a friend class to be used by the Quad
	public:
		Quad() = default;
		static Quad createCentralHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents); //!< Calculate central half extents of the quad
	};

	/** \class Renderer2D
	** \brief Class which allows the rendering of simple 2D primitive
	*/
	class Renderer2D {
	private:

		/** \struct GlyphData
		*\brief properties for the character glyph
		\param size vec2 - size of the character
		\param bearing vec2 - bearing of the character glyph
		\param advance float - offset value for the character
		\param texture shared_ptr<SubTexture> - texture for the glyph
		*/
		struct GlyphData {
			glm::vec2 size; //!< Size of the character 
			glm::vec2 bearing; //!< Bearing of the character
			float advance; //!< Advance of the character
			std::shared_ptr<SubTexture> subTexture; //!< Texture for the character
		};

		/** \struct InternalData
		*\brief all Renderer properties used for rendering to be used as a static object
		\param defaultTexture shared_ptr<OpenGLTexture> - default white texture
		\param fontTexture shared_ptr<OpenGLTexture> - font texture
		\param shader shared_ptr<OpenGLShader> - shader used for the 2D object
		\param VAO shared_ptr<VertexArray> - vertex array for the 2D quad
		\param quadUBO shared_ptr<UniformBuffer> - uniform buffer for the 2D quad
		\param defaultSubTexture shared_ptr<SubTexture> - default sub texture
		\param quad array<vec4, 4> - Quad position
		\param textureUnits array<int32_t, 32> - Texture units
		\param vertices vector<Render2DVertex> - Quad vertices
		\param glyphData vector<GlyphData> - Struct of glyph data
		\param batchSize uint32_t - batch size per draw call
		\param defaultTint vec4 - Default white tint
		\param model mat4 - Model matrix
		\param drawCount uint32_t - draw count

		\param ft FT_Library - freetype library
		\param font FT_Face - freetype font face
		\param glyphAtlas TextureAtlas - texture atlas for the font
		\param firstChar char - first typeable char ascii code (32 = Space)
		\param lastChar char - last typeable char ascii code (126 = ~)
		*/
		struct InternalData {
			std::shared_ptr<OpenGLTexture> defaultTexture; //!< Empty white texture
			std::shared_ptr<OpenGLTexture> fontTexture; //!< Font texture
			std::shared_ptr<OpenGLShader> shader; //!< Shader
			std::shared_ptr<OpenGLVertexArray> VAO; //!< Vertex array for the 2D quad
			std::shared_ptr<OpenGLUniformBuffer> quadUBO; //!< Uniform buffer for the 2D quad
			std::shared_ptr <SubTexture> defaultSubTexture; //!< Default sub texture
			std::array<glm::vec4, 4> quad; //!< Quad postion
			std::array<int32_t, 32> textureUnits; //!< Texture units / slots
			std::vector<Renderer2DVertex> vertices; //!< Quad verticies
			std::vector<GlyphData> glyphData; //!< Glyph data structure
			static const uint32_t batchSize = 8192; //!< Batch size per draw call
			glm::vec4 defaultTint; //!< Default white tint ( Colour / Albedo )
			glm::mat4 model; //!< Matrix model
			uint32_t drawCount; //!< Draw count

			FT_Library ft; //!< Freetype library
			FT_Face font; //!< Freetype font face
			TextureAtlas glyphAtlas; //!< Texture atlas for the font
			unsigned char firstGlyph = 32; //!< First character
			unsigned char lastGlyph = 126; //!< Last character
		};

		static void RtoRGBA(unsigned char* DSTbuffer, unsigned char* SRCBuffer, uint32_t width, uint32_t height); //! Function to convert the buffer to RGBA format
		static std::shared_ptr<InternalData> s_data; //!< Internal data of the renderer
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
		static void flush(); //!< Render all geometry
	};
}