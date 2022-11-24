/** \file GLFW_OpenGL_GC.cpp */
#include "engine_pch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "platform/GLFW/GLFW_OpenGL_GC.h"
#include "systems/loggerSys.h"

namespace Engine {
	void GLFW_OpenGL_GC::init() {
		glfwMakeContextCurrent(m_window);
		auto result = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

		if (!result) LoggerSys::error("Could not create OpenGL context for current GLFW Window: {0}", result);

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(
			[](
				GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,
				GLsizei length,
				const GLchar* message,
				const void* userParam
				)
			{
				switch (severity) {
				case GL_DEBUG_SEVERITY_HIGH:
					LoggerSys::error(message);
					break;
				case GL_DEBUG_SEVERITY_MEDIUM:
					LoggerSys::warn(message);
					break;
				case GL_DEBUG_SEVERITY_LOW:
					LoggerSys::info(message);
					break;
				case GL_DEBUG_SEVERITY_NOTIFICATION:
					LoggerSys::trace(message);
					break;
				}
			}
		,nullptr);
	}
	void GLFW_OpenGL_GC::swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}
