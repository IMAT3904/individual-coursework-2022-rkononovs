/** \file OpenGLShader.h */
#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace Engine {
	class OpenGLShader {
	private:
		uint32_t m_OpenGL_ID; //!< Render ID

		void compileAndLink(const char* vertexShaderSrc, const char* fragmentShaderSrc); //!< Compile and link the shaders
	public:
		OpenGLShader(const char* vertexFilePath, const char* fragmentFilepath); //!< Constructor which takes vertex and fragment shader path
		OpenGLShader(const char* filepath); //!< Constructor which takes path to combined shader
		~OpenGLShader(); //!< Default destructor

		inline uint32_t getRenderID() const { return m_OpenGL_ID; } //!< Get OpenGL ID

		void uploadInt(const char* name, int value); //!< Upload integer
		void uploadIntArray(const char* name, int32_t* values, uint32_t count); //!< Upload integer array
		void uploadFloat(const char* name, float value); //!< Upload float
		void uploadFloat2(const char* name, const glm::vec2& value); //!< Upload vector of 2 floats
		void uploadFloat3(const char* name, const glm::vec3& value); //!< Upload vector of 3 floats
		void uploadFloat4(const char* name, const glm::vec4& value); //!< Upload vector of 4 floats
		void uploadMat4(const char* name, const glm::mat4& value); //!< Upload 4x4 matrix
	};
}
