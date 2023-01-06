/** \file TextureUnitManager.cpp */

#include "engine_pch.h"
#include "rendering/TextureUnitManager.h"

namespace Engine {
	TextureUnitManager::TextureUnitManager(){
	}
	void TextureUnitManager::clear(){
		m_head = 0;
		m_tail = 0;
		m_full = false;
		std::fill(m_buffer.begin(), m_buffer.end(), 0xFFFFFFFF);
	}
	bool TextureUnitManager::getUnit(uint32_t textureID, uint32_t& textureUnit)
	{
		// Is the texture already bound
		for (int i = m_tail; i < m_head; i++) {
			if (m_buffer.at(i) == textureID) {
				textureUnit = i;
				return false;
			}
		}
		// Texture unit is not bound

		// Is there space in the buffer
		if (m_full) clear();

		// Put textureID in the buffer
		m_buffer.at(m_head) = textureID;
		textureUnit = m_head;
		
		// Checking if over capacity
		m_head = (++m_head) % m_capacity;
		if (m_head == m_tail) m_full = true;

		return true;
	}
}