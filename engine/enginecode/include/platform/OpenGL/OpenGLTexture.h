/** \file OpenGLTexture.h */
#pragma once

#include <cstdint>
#include "rendering/RendererCommon.h"

namespace Engine {
	/**
	\class OpenGLTexture
	\brief OpenGL implementation of a texture class
	*/
	class OpenGLTexture {
	private:
		uint32_t m_OpenGL_ID; //!< OpenGL ID
		uint32_t m_width; //!< Texture width
		uint32_t m_height; //!< Texture height
		uint32_t m_channels; //!< Numbers of channels in texture

		void init(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data, uint32_t slot); //!< Initialize texture
	public:
		OpenGLTexture(const char* filepath, uint32_t slot); //!< Constructor that tike file path and creates texture
		OpenGLTexture(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data, uint32_t slot); //!< Constructor that takes data and creates texture
		~OpenGLTexture(); //!< Destructor

		void edit(uint32_t xOffeset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char* data); //!< Edit the texture
		void bindToSlot(uint32_t slot); //!< Bind texture to slot

		inline uint32_t getRenderID() const { return m_OpenGL_ID; } //!< Get OpenGL ID
		inline uint32_t getWidth() { return m_width; } //!< Get texture width
		inline uint32_t getHeight() { return m_height; } //!< Get texture height
		inline uint32_t getWidthf() { return static_cast<float>(m_width); } //!< Get texture width as float
		inline uint32_t getHeightf() { return static_cast<float>(m_height); } //!< Get texture height as float
		inline uint32_t getChannels() { return m_channels; } //!< Get the numbers of channels
	};
}