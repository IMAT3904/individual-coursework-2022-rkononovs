/** \file TextureUnitManager.h */
#pragma once

#include <vector>
#include <unordered_map>

namespace Engine {
	class TextureUnitManager {
	private:
		//uint32_t m_capacity; //!< Capacity of the ring buffer
		//uint32_t m_head = 0; //!< Head of the buffer
		//uint32_t m_tail = 0; //!< Tail of the buffer
		std::vector<uint32_t> m_textureIds; //!< Internal buffer
		std::unordered_map<uint32_t, uint32_t> m_textureUnits;
		//bool m_full = false; //!< Is the buffer full
		size_t m_nextUnit = 0;
	public:
		TextureUnitManager(size_t capacity); //: m_capacity(capacity), m_buffer(capacity, 0xFFFFFFFF) {}; //!< Constructor which takes a capacity
		void clear(); //!< Clear and rest the buffer
		bool getUnit(uint32_t textureID, uint32_t& textureUnit); //!< Returns whether or not the texture need binding needs binding to unit. Texture unit is always set to unit
		inline bool full() { return m_nextUnit == m_textureIds.capacity(); }; //!< Is the buffer full

	};
}