/* textureAtlas.h */
#pragma once

#include <vector>
#include "rendering/subTexture.h"

namespace Engine {
	struct SimpleRect { int32_t x, y, w, h; };

	class TextureAtlas {
	private:
		std::vector<SimpleRect> m_spaces;
		std::shared_ptr<OpenGLTexture> m_baseTexture;
	public:
		TextureAtlas(glm::ivec2 size = { 4096, 4096 }, uint32_t channels = 4, uint32_t reservedSpaces = 32);
		bool add(const char* filepath, std::shared_ptr<SubTexture>& result);
		bool add(int32_t width, int32_t height, uint32_t channels, unsigned char* data, std::shared_ptr<SubTexture>& result);
		inline uint32_t getChannels() const { return m_baseTexture->getChannels(); }
		inline uint32_t getID() const { return m_baseTexture->getRenderID(); }
		inline std::shared_ptr<OpenGLTexture> getBaseTexture() const { return m_baseTexture; }
	};
}
