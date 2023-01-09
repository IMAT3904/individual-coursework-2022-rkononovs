/* \file textureAtlas.cpp */

#include "engine_pch.h"
#include "rendering/textureAtlas.h"
//#include <algorithm>
#include <stb_image.h>

namespace Engine {
	TextureAtlas::TextureAtlas(glm::ivec2 size, uint32_t channels, uint32_t reservedSpaces){
		m_baseTexture.reset(new OpenGLTexture(size.x, size.y, channels, nullptr, 0));

		m_spaces.reserve(reservedSpaces);
		m_spaces.push_back({ 0,0,size.x,size.y });
	}
	bool TextureAtlas::add(const char* filepath, std::shared_ptr<SubTexture>& result){
		int32_t width, height, channels;
		unsigned char* data = stbi_load(filepath, &width, &height, &channels, static_cast<int>(getChannels()));

		if (data) return add(width, height, channels, data, result);

		stbi_image_free(data);
		return false;
	}
	bool TextureAtlas::add(int32_t width, int32_t height, uint32_t channels, unsigned char* data, std::shared_ptr<SubTexture>& result){
		if (channels != getChannels()) return false; // Early exit as channels don't match

		if (width == 0 || height == 0) {
			result.reset(new SubTexture(m_baseTexture, glm::vec2(0.f), glm::vec2(0.f)));
			return true;
		}
		for (auto it = m_spaces.begin(); it != m_spaces.end(); ++it) {
			auto& space = *it;
			// Does the texture fit this space
			if (width < space.w && height < space.h) {
				// Texture fits
				m_baseTexture->edit(space.x, space.y, width, height, data);

				//Set subTexture result
				glm::vec2 UVStart(static_cast<float>(space.x) / m_baseTexture->getWidthf(), static_cast<float>(space.y) / m_baseTexture->getHeightf());
				glm::vec2 UVEnd(static_cast<float>(space.x + width) / m_baseTexture->getWidthf(), static_cast<float>(space.y + height) / m_baseTexture->getHeightf());

				result.reset(new SubTexture(m_baseTexture, UVStart, UVEnd));

				//Sort out remaining spaces

				//Case 1: Texture matches space size, delete space
				if (width == space.w && height == space.h){
					m_spaces.erase(it);
					return true;
				}


				//Case 2: Texture width matches space width, height do not match - split the space horizontally in two
				//
				// -----------			----------
				// |         |  becomes |        |
				// |  Space  |			|--------|
				// |         |			|  Space |
				// -----------			----------
				else if (width == space.w){
					space.y += height;
					space.h -= height;
					return true;
				}

				//Case 3: Texture width matches height, width do not match - split the space vertically in two
				//
				// -----------			----------
				// |         |  becomes |   | Sp |
				// |  Space  |			|   | ac |
				// |         |			|   | e  |
				// -----------			----------

				else if (height == space.h){
					space.x += width;
					space.w -= width;
					return true;
				}

				//Case 4 Texture height and width do not match = split the space horizontally and vertically
				//
				// -----------			----------
				// |         |  becomes |   | Sp |
				// |  Space  |			|---| ac |
				// |         |			|Spa| e  |
				// -----------			----------
				else{
					SimpleRect newRect = { space.x, space.y + height, width, space.h - height };

					space.x += width;
					space.w -= width;
					m_spaces.push_back(newRect);

					std::sort(m_spaces.begin(), m_spaces.end(), [](SimpleRect& a, SimpleRect& b)
						{return a.w < b.w; }
					);

					return true;
				}
			}
		}

		return false;
	}
}