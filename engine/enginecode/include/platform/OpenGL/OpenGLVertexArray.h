/** \file OpenGLVertexArray.h */
#pragma once

#include <vector>
#include <memory>
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"

namespace Engine {
	class OpenGLVertexArray {
	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		uint32_t m_attributeIndex = 0;//!< Vertex array atribute index

		std::vector<std::shared_ptr<OpenGLVertexBuffer>> m_vertexBuffer;
		std::shared_ptr<OpenGLIndexBuffer> m_indexBuffer;
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		void addVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer>& vertexBuffer);
		void setIndexBuffer(const std::shared_ptr<OpenGLIndexBuffer>& indexBuffer);
		inline uint32_t getRenderID() const { return m_OpenGL_ID; }
		inline uint32_t getDrawnCount(){
			if (m_indexBuffer) { m_indexBuffer->getCount(); }
			else { return 0; }
		}
	};
}
