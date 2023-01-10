/** \file subTexture.h */
#pragma once
#include <include/platform/OpenGL/OpenGLTexture.h>
#include <memory>
#include <glm/glm.hpp>


namespace Engine
{
	/** \class SubTexture
	*\brief abstraction for loading texture
	*/
	class SubTexture {
	private:
		std::shared_ptr<OpenGLTexture> m_texture;
		glm::vec2 m_UVStart = glm::vec2(0.f); //!< UV start points
		glm::vec2 m_UVEnd = glm::vec2(1.f); //!< UV end points
		glm::vec2 m_size; //!< Size in pixels
	public:
		SubTexture(); //!< Default constructor
		SubTexture(const std::shared_ptr<OpenGLTexture>& texture, const glm::vec2& UVStart, const glm::vec2& UVEND); //!< Constructor with a pointer to the OpenGLTexture and UV start and end
		inline glm::vec2 getUVStart() const { return m_UVStart; }; //!< Get UV start points
		inline glm::vec2 getUVEnd() const { return m_UVEnd; }; //!< Get UV end points
		glm::ivec2 getSize() const { return m_size; }; //!< Get size
		glm::vec2 getSizef() const { return { static_cast<float>(m_size.x), static_cast<float>(m_size.y) }; }; //!< Get size in float
		inline uint32_t getWidth() const { return m_size.x; } //!< Get width
		inline uint32_t getHeight() const { return m_size.y; } //!< Get height
		inline uint32_t getWidthf() const { return  static_cast<float>(m_size.x); } //!< Get width in float
		inline uint32_t getHeightf() const { return static_cast<float>(m_size.y); } //!< Get height in float
		float transformU(float U); //!< Transform original to U atlased co-ords
		float transformV(float V); //!< Transform original to V atlased co-ords
		glm::vec2 transformUV(glm::vec2 UV); //!< Transform original to UV atlased co-ords
		inline const std::shared_ptr<OpenGLTexture> getBaseTexture() const { return m_texture; }; //!< Get base texture
	};
}