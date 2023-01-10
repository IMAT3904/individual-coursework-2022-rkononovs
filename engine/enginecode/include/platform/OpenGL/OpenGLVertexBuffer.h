/** \file OpenGLVertexBuffer.h */
#pragma once

#include "rendering/bufferLayout.h"

namespace Engine {
	/**
	\class OpenGLVertexBuffer
	\brief OpenGL implementation of Vertex Buffer
	*/
	class OpenGLVertexBuffer {
	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		VertexBufferLayout m_layout;
	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size, VertexBufferLayout layout); //!< Constructor
		~OpenGLVertexBuffer(); //! Destructor
		void edit(void* vertices, uint32_t size, uint32_t offset); //!< Edit vertices with offset
		inline uint32_t getRenderID() const { return m_OpenGL_ID; } //!< Get OPen GL ID
		inline const VertexBufferLayout& getLayout() const { return m_layout; } //!< Get layout
	};
}