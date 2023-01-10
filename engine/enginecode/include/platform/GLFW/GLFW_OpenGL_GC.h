/** \file GLFW_OpenGL_GC.h */
#pragma once

#include <core/graphicsContext.h>

namespace Engine {
	/**
	\class GLFW_OpenGL_GC
	\brief Graphic context that uses GLFW implementation.
	*/
	class GLFW_OpenGL_GC : public GraphicsContext {
	private:
		GLFWwindow* m_window; //!< Pointer to GLFW Window
	public:
		GLFW_OpenGL_GC(GLFWwindow* win) : m_window(win) {} //!< Constructor
		virtual void init() override; //!< Initialize graphics context for given window
		virtual void swapBuffers() override; //!< Swap the front and back buffer
	};
}