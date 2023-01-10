/** \file OpenGLVertexArray.h */
#pragma once

#include <vector>
#include <memory>
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"

namespace Engine {
	/**
	\class OpenGLVertexArray
	\brief OpenGL implementation of Vertex Array
	*/
	class OpenGLVertexArray {
	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		uint32_t m_attributeIndex = 0;//!< Vertex array atribute index

		std::vector<std::shared_ptr<OpenGLVertexBuffer>> m_vertexBuffer; //!< Vector of pointers to vertex buffers
		std::shared_ptr<OpenGLIndexBuffer> m_indexBuffer; //!< Pointer to index buffer
	public:
		OpenGLVertexArray(); //!< Constructor
		~OpenGLVertexArray(); //!< Destructor
		void addVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer>& vertexBuffer); //!< Add vertex buffer
		void setIndexBuffer(const std::shared_ptr<OpenGLIndexBuffer>& indexBuffer); //!< Set index buffer

		inline std::shared_ptr<OpenGLIndexBuffer> getIndexBuffer() { return m_indexBuffer; }; //!< Get index buffer
		inline std::vector<std::shared_ptr<OpenGLVertexBuffer>> getVertexBuffers() { return m_vertexBuffer; } //!< Get vertex buffers
		inline uint32_t getRenderID() const { return m_OpenGL_ID; } //!< Get OpenGL ID
		inline uint32_t getDrawnCount(){ //!< Get draw count
			if (m_indexBuffer) { m_indexBuffer->getCount(); }
			else { return 0; }
		}
	};
}
