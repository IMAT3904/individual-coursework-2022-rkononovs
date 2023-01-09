/** \file subTexture.h */
#pragma once
#include <include/platform/OpenGL/OpenGLTexture.h>
#include <memory>
#include <glm/glm.hpp>


namespace Engine
{
	class SubTexture {
	private:
		std::shared_ptr<OpenGLTexture> m_texture;
		glm::vec2 m_UVStart = glm::vec2(0.f);
		glm::vec2 m_UVEnd = glm::vec2(1.f);
		glm::vec2 m_size; //!< Size in pixels
	public:
		SubTexture();
		SubTexture(const std::shared_ptr<OpenGLTexture>& texture, const glm::vec2& UVStart, const glm::vec2& UVEND);
		inline glm::vec2 getUVStart() const { return m_UVStart; };
		inline glm::vec2 getUVEnd() const { return m_UVEnd; };
		glm::ivec2 getSize() const { return m_size; };
		glm::vec2 getSizef() const { return { static_cast<float>(m_size.x), static_cast<float>(m_size.y) }; };
		inline uint32_t getWidth() const { return m_size.x; }
		inline uint32_t getHeight() const { return m_size.y; }
		inline uint32_t getWidthf() const { return  static_cast<float>(m_size.x); }
		inline uint32_t getHeightf() const { return static_cast<float>(m_size.y); }
		float transformU(float U); //!< Transform original to atlased co-ords
		float transformV(float V);
		glm::vec2 transformUV(glm::vec2 UV);
		inline const std::shared_ptr<OpenGLTexture> getBaseTexture() const { return m_texture; };
	};
}