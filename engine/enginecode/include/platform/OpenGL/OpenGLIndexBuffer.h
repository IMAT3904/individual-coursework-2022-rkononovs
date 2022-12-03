/** \file OpenGLIndexBuffer.h */
#pragma once

#include <cstdint>
namespace Engine {
	class OpenGLIndexBuffer {
	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		uint32_t m_count; //!< Draw count
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer();

		inline uint32_t getRenderID() const { return m_OpenGL_ID; }
		inline uint32_t getCount() const { return m_count; }
	};
}