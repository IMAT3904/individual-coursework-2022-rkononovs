/** \file TextureUnitManager.h */
#pragma once

#include <vector>
#include <unordered_map>

namespace Engine {
	class TextureUnitManager {
	private:
		std::vector<uint32_t> m_textureIds; //!< Internal buffer
		std::unordered_map<uint32_t, uint32_t> m_textureUnits;
		size_t m_nextUnit = 0;
	public:
		TextureUnitManager(size_t capacity); //!< Constructor which takes a capacity
		void clear(); //!< Clear and rest the buffer
		bool getUnit(uint32_t textureID, uint32_t& textureUnit); //!< Returns whether or not the texture need binding needs binding to unit. Texture unit is always set to unit
		inline bool full() { return m_nextUnit == m_textureIds.capacity(); }; //!< Is the buffer full

	};
}