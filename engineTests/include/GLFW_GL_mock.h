#pragma once

#include "include/platform/GLFW/GLFWSystem.h"
#include "include/platform/GLFW/GLFWWindowImpl.h"

class GLFW_GL_mock {
public:
	GLFW_GL_mock();
	~GLFW_GL_mock();

	std::shared_ptr<Engine::System> glfwSystem;
	std::shared_ptr<Engine::Window> glfwWindow;
};