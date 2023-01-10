/** \file textureAtlas.h */
#pragma once

#include <vector>
#include "rendering/subTexture.h"

namespace Engine {
	/** \struct SimpleRect
	*\brief properties for a rectangle
	\param w int32_t - width of the rectangle
	\param h int32_t - height of the rectangle
	\param x int32_t - x position
	\param y int32_t - y position
	*/
	struct SimpleRect { int32_t x, y, w, h; };

	/**
	\class TextureAtlas
	* \brief class to store textures to be rendered
	*/
	class TextureAtlas {
	private:
		std::vector<SimpleRect> m_spaces; //!< Spaces in the texture atlas
		std::shared_ptr<OpenGLTexture> m_baseTexture; //!< Texture to hold subtexture pixel data
	public:
		TextureAtlas(glm::ivec2 size = { 4096, 4096 }, uint32_t channels = 4, uint32_t reservedSpaces = 32); //!< Constructor with size and channels
		bool add(const char* filepath, std::shared_ptr<SubTexture>& result); //!< Add subtexture from file
		bool add(int32_t width, int32_t height, uint32_t channels, unsigned char* data, std::shared_ptr<SubTexture>& result); //!< Add subtexture from data

		inline uint32_t getChannels() const { return m_baseTexture->getChannels(); } //!< Get channels of the texture
		inline uint32_t getID() const { return m_baseTexture->getRenderID(); } //!< Get render id

		inline std::shared_ptr<OpenGLTexture> getBaseTexture() const { return m_baseTexture; } //!< Get base texture
	};
}
