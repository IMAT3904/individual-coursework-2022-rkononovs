/** \file TextureUnitManager.cpp */

#include "engine_pch.h"
#include "rendering/TextureUnitManager.h"

namespace Engine {
	TextureUnitManager::TextureUnitManager(size_t capacity){
		// Resize the texture ID's
		m_textureIds.resize(capacity);

		// Fill with the max value
		std::fill(m_textureIds.begin(), m_textureIds.end(), std::numeric_limits<uint32_t>::max());

		// Create to space in map
		m_textureUnits.reserve(capacity * 2);
	}
	void TextureUnitManager::clear(){
		std::fill(m_textureIds.begin(), m_textureIds.end(), std::numeric_limits<uint32_t>::max());
		m_textureUnits.clear();
		m_nextUnit = 0;
	}
	bool TextureUnitManager::getUnit(uint32_t textureID, uint32_t& textureUnit){
		auto unitItr = m_textureUnits.find(textureID);
		if (unitItr != m_textureUnits.end()) {
			textureUnit = unitItr->second;
			return false;
		}

		if (full()) {
			textureUnit = -1;
			return true;
		}
		else {
			textureUnit = m_nextUnit;
			
			m_textureIds[m_nextUnit] = textureID;
			m_textureUnits[textureID] = m_nextUnit;

			m_nextUnit++;

			return true;
		}
	}
}