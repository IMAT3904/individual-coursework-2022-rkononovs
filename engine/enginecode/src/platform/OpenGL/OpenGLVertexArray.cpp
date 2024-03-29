/** \file OpenGLVertexArray.cpp */
#include "engine_pch.h"
#include <glad/glad.h>
#include "platform/OpenGL/OpenGLVertexArray.h"

namespace Engine {
	namespace STD {
		static GLenum toGLType(ShaderDataType type) {
			switch (type) {
			case ShaderDataType::FlatByte: return GL_BYTE;
			case ShaderDataType::Byte4   : return GL_UNSIGNED_BYTE;
			case ShaderDataType::FlatInt : return GL_INT;
			case ShaderDataType::Int     : return GL_INT;
			case ShaderDataType::Float   : return GL_FLOAT;
			case ShaderDataType::Float2  : return GL_FLOAT;
			case ShaderDataType::Float3  : return GL_FLOAT;
			case ShaderDataType::Float4  : return GL_FLOAT;
			case ShaderDataType::Mat4    : return GL_FLOAT;
			default: return GL_INVALID_ENUM;
			}
		}
	}
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_OpenGL_ID);
		glBindVertexArray(m_OpenGL_ID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_OpenGL_ID);
	}
	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer>& vertexBuffer)
	{
		m_vertexBuffer.push_back(vertexBuffer);

		glBindVertexArray(m_OpenGL_ID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getRenderID());

		const auto& layout = vertexBuffer->getLayout();
		for (const auto& element : layout) {
			uint32_t normalized = GL_FALSE;
			if (element.m_normalized) { normalized = GL_TRUE; }
			glEnableVertexAttribArray(m_attributeIndex);
			if (element.m_dataType == ShaderDataType::FlatInt || element.m_dataType == ShaderDataType::FlatByte) {
				glVertexAttribIPointer(
					m_attributeIndex,
					STD::componentCount(element.m_dataType),
					STD::toGLType(element.m_dataType),
					layout.getStride(),
					(const void*)element.m_offset);
				m_attributeIndex++;
			}
			else {
				glVertexAttribPointer(
					m_attributeIndex,
					STD::componentCount(element.m_dataType),
					STD::toGLType(element.m_dataType),
					normalized,
					layout.getStride(),
					(void*)element.m_offset);
				m_attributeIndex++;
			}
		}
	}
	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<OpenGLIndexBuffer>& indexBuffer)
	{
		m_indexBuffer = indexBuffer;
	}
}