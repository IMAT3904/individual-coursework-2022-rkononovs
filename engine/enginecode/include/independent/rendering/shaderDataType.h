/** \file shaderDataType.h */
#pragma once

#include <cstdint>

namespace Engine {
	/**
	\enum ShaderDataType
	*\brief Enum for shader data types
	*/
	enum class ShaderDataType {
		None = 0, FlatByte, Byte4, Short, Short2, Short3, Short4, Float, Float2, Float3, Float4, FlatInt, Int, Mat3, Mat4
	};

	namespace STD {
		//! Get size of the shader data type
		/*!
		\param type ShaderDataType - shader data type
		*/
		static uint32_t size(ShaderDataType type) {
			switch (type) {
			case ShaderDataType::FlatByte:return 1;
			case ShaderDataType::Byte4   :return 1 * 4;
			case ShaderDataType::Short   :return 2;
			case ShaderDataType::Short2  :return 2 * 2;
			case ShaderDataType::Short3  :return 2 * 3;
			case ShaderDataType::Short4  :return 2 * 4;
			case ShaderDataType::Float   :return 4;
			case ShaderDataType::Float2  :return 4 * 2;
			case ShaderDataType::Float3  :return 4 * 3;
			case ShaderDataType::Float4  :return 4 * 4;
			case ShaderDataType::FlatInt :return 4;
			case ShaderDataType::Int     :return 4;
			case ShaderDataType::Mat3    :return 4 * 3 * 3;
			case ShaderDataType::Mat4    :return 4 * 4 * 4;
			default: return 0;
			}
		}

		//! Get component count of the shader data type
		/*!
		\param type ShaderDataType - shader data type
		*/
		static uint32_t componentCount(ShaderDataType type) {
			switch (type) {
			case ShaderDataType::FlatByte:return 1;
			case ShaderDataType::Byte4   :return 4;
			case ShaderDataType::Short   :return 1;
			case ShaderDataType::Short2  :return 2;
			case ShaderDataType::Short3  :return 3;
			case ShaderDataType::Short4  :return 4;
			case ShaderDataType::Float   :return 1;
			case ShaderDataType::Float2  :return 2;
			case ShaderDataType::Float3  :return 3;
			case ShaderDataType::Float4  :return 4;
			case ShaderDataType::FlatInt :return 1;
			case ShaderDataType::Int     :return 1;
			case ShaderDataType::Mat3    :return 3 * 3;
			case ShaderDataType::Mat4    :return 4 * 4;
			default: return 0;
			}
		}

		//! Get std 140 alignment of the shader data type
		/*!
		\param type ShaderDataType - shader data type
		*/
		static uint32_t std140alignment(ShaderDataType type) {
			switch (type) {
			case ShaderDataType::Byte4: return 1 * 4;
			case ShaderDataType::Short: return 2;
			case ShaderDataType::Short2: return 2 * 2;
			case ShaderDataType::Short3: return 2 * 4;
			case ShaderDataType::Short4: return 2 * 4;
			case ShaderDataType::Float: return 4;
			case ShaderDataType::Float2: return 4 * 2;
			case ShaderDataType::Float3: return 4 * 4;
			case ShaderDataType::Float4: return 4 * 4;
			case ShaderDataType::Mat3  : return 4 * 3 * 3;
			case ShaderDataType::Mat4  : return 4 * 4 * 4;
			default: return 0;
			}
		}
	}
}