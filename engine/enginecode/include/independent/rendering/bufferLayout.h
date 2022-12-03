/** \file bufferLayout.h */
#pragma once

#include <vector>

#include "shaderDataType.h"

namespace Engine {

	/**
	\class BufferElement
	A class which hold a single element in a buffer layout
	*/
	class BufferElement {
	public:
		ShaderDataType m_dataType; //!< The type of data
		uint32_t m_size; //!< The size of data
		uint32_t m_offset; //!< The offset of data
		bool m_normalized; //!< Normalization of data

		BufferElement() {} //!< Default constructor
		BufferElement(ShaderDataType dataType, bool normalized = false) :
			m_dataType(dataType),
			m_size(STD::size(dataType)),
			m_offset(0),
			m_normalized(normalized){} //!< Constructor with parameters
	};

	/** \class BufferLayout
	* Abstraction of the buffer layout
	*/
	class BufferLayout {
	private:
		std::vector<BufferElement> m_elements; //!< Buffer elements
		uint32_t m_stride; //!< Width in bytes of the buffer line
		void calcStrideAndOffset(); //!< Calculate stride and offsets based on elements 
	public:
		BufferLayout() {};
		BufferLayout(const std::initializer_list<BufferElement>& element) : m_elements(element) { calcStrideAndOffset(); }
		inline uint32_t getStride() const { return m_stride; }
		void addElement(BufferElement element);
		inline std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		inline std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		inline std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		inline std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
	};
}
