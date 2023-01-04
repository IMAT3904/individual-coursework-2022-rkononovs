/** \file TextureUnitManager.h */
#pragma once

#include <vector>

namespace Engine {
	class TextureUnitManager {
	private:
		uint32_t m_capacity; //!< Capacity of the ring buffer
		uint32_t m_head = 0; //!< Head of the buffer
		uint32_t m_tail = 0; //!< Tail of the buffer
		std::vector<uint32_t> m_buffer; //!< Internal buffer
		bool m_full = false; //!< Is the buffer full
	public:
		TextureUnitManager(uint32_t capacity) : m_capacity(capacity), m_buffer(capacity, 0xFFFFFFFF) {}; //!< Constructor which takes a capacity
		void clear(); //!< Clear and rest the buffer
		bool getUnit(uint32_t textureID, uint32_t& textureUnit); //!< Returns whether or not the texture need binding needs binding to unit. Texture unit is always set to unit
		inline bool full() { return m_full; } //!< Is the buffer full

	};
}