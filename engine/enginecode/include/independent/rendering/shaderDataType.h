/** \file shaderDataType.h */
#pragma once

#include <cstdint>

namespace Engine {
	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4
	};

	namespace STD {
		static uint32_t size(ShaderDataType type) {
			switch (type) {
			case ShaderDataType::Float : return 4;
			case ShaderDataType::Float2: return 4 * 2;
			case ShaderDataType::Float3: return 4 * 3;
			case ShaderDataType::Float4: return 4 * 4;
			default: return 0;
			}
		}

		static uint32_t componentCount(ShaderDataType type) {
			switch (type) {
			case ShaderDataType::Float : return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			default: return 0;
			}
		}
	}
}