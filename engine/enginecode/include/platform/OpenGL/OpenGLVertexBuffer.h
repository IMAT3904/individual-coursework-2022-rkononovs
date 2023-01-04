/** \file OpenGLVertexBuffer.h */
#pragma once

#include "rendering/bufferLayout.h"

namespace Engine {
	class OpenGLVertexBuffer {
	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		VertexBufferLayout m_layout;
	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size, VertexBufferLayout layout);
		~OpenGLVertexBuffer();
		void edit(void* vertices, uint32_t size, uint32_t offset);
		inline uint32_t getRenderID() const { return m_OpenGL_ID; }
		inline const VertexBufferLayout& getLayout() const { return m_layout; }
	};
}