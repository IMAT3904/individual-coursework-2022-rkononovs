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
	}
	void GLFW_OpenGL_GC::swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}
