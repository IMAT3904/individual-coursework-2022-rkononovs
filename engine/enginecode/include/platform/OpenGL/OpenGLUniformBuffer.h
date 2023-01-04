/** \file OpenGLUniformBuffer.h */
#pragma once
#include "rendering/bufferLayout.h"
#include "OpenGLShader.h"
#include <unordered_map>
#include <memory>


namespace Engine {
	class OpenGLUniformBuffer {
	private:
		uint32_t m_OpenGL_ID; //!< OpenGL ID
		UniformBufferLayout m_layout; //!< Uniform Buffer Layout
		uint32_t m_blockNumber; //!< Block number for UBO
		std::unordered_map<const char*, std::pair<uint32_t, uint32_t>> m_uniformCache; //!< Stores uniform names with offsets and sizes

		static uint32_t s_blockNumber; //!< Global block number
	public:
		OpenGLUniformBuffer(const UniformBufferLayout& layout); //!< Constructor
		~OpenGLUniformBuffer();
		void attachShaderBlock(const std::shared_ptr<OpenGLShader>& shader, const char* blockname);
		void uploadData(const char* uniformName, void* data);
		inline uint32_t getRenderID() const { return m_OpenGL_ID; }
		inline const UniformBufferLayout& getLayout() const { return m_layout; }
	};
}
