/** \file bufferLayout.h */
#pragma once

#include <vector>

#include "shaderDataType.h"

namespace Engine {

	/**
	\class VertexBufferElement
	A class which hold a single element in a vertex buffer layout
	*/
	class VertexBufferElement {
	public:
		ShaderDataType m_dataType; //!< The type of data
		uint32_t m_size; //!< The size of data
		uint32_t m_offset; //!< The offset of data
		bool m_normalized; //!< Normalization of data

		VertexBufferElement() {} //!< Default constructor
		VertexBufferElement(ShaderDataType dataType, bool normalized = false) :
			m_dataType(dataType),
			m_size(STD::size(dataType)),
			m_offset(0),
			m_normalized(normalized){} //!< Constructor with parameters
	};

	/**
	\class UniformBufferElement
	A class which hold a single element in a uniform buffer layout
	*/
	class UniformBufferElement {
	public:
		const char* m_name;
		ShaderDataType m_dataType; //!< The type of data
		uint32_t m_size; //!< The size of data
		uint32_t m_offset; //!< The offset of data

		UniformBufferElement() {} //!< Default constructor
		UniformBufferElement(const char* name, ShaderDataType dataType) :
			m_name(name),
			m_dataType(dataType),
			m_size(STD::std140alignment(dataType)),
			m_offset(0) {} //!< Constructor with parameters
	};

	/** \class BufferLayout
	* Abstraction of the buffer layout
	*/
	template<class G>
	class BufferLayout {
	private:
		std::vector<G> m_elements; //!< Buffer elements
		uint32_t m_stride; //!< Width in bytes of the buffer line
		void calcStrideAndOffset(); //!< Calculate stride and offsets based on elements 
	public:
		BufferLayout<G>() {};
		BufferLayout<G>(const std::initializer_list<G>& element) : m_elements(element) { calcStrideAndOffset(); }
		inline uint32_t getStride() const { return m_stride; }
		void addElement(G element);
		inline typename std::vector<G>::iterator begin() { return m_elements.begin(); }
		inline typename std::vector<G>::iterator end() { return m_elements.end(); }
		inline typename std::vector<G>::const_iterator begin() const { return m_elements.begin(); }
		inline typename std::vector<G>::const_iterator end() const { return m_elements.end(); }
	};

	template<class G>
	void BufferLayout<G>::addElement(G element) {
		m_elements.push_back(element);
		calcStrideAndOffset();
	}

	template<class G>
	void BufferLayout<G>::calcStrideAndOffset() {
		uint32_t offset = 0;

		for (auto& element : m_elements) {
			element.m_offset = offset;
			offset += element.m_size;
		}

		m_stride = offset;
	}

	using VertexBufferLayout = BufferLayout<VertexBufferElement>;
	using UniformBufferLayout = BufferLayout<UniformBufferElement>;
}
