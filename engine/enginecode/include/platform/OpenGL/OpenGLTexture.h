/* \file OpenGLTexture.h */
#pragma once

#include <cstdint>
#include "rendering/RendererCommon.h"

namespace Engine {
	class OpenGLTexture {
	private:
		uint32_t m_OpenGL_ID;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_channels;

		void init(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data, uint32_t slot);
	public:
		OpenGLTexture(const char* filepath, uint32_t slot);
		OpenGLTexture(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data, uint32_t slot);
		~OpenGLTexture();

		void edit(uint32_t xOffeset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char* data);
		void bindToSlot(uint32_t slot);

		inline uint32_t getRenderID() const { return m_OpenGL_ID; } //!< Get OpenGL ID
		inline uint32_t getWidth() { return m_width; }
		inline uint32_t getHeight() { return m_height; }
		inline uint32_t getHeightf() { return static_cast<float>(m_height); }
		inline uint32_t getWidthf() { return static_cast<float>(m_width); }
		inline uint32_t getChannels() { return m_channels; }
	};
}