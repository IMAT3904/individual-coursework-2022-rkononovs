#include "GLFW_GL_mock.h"

static	GLFW_GL_mock mock;

GLFW_GL_mock::GLFW_GL_mock(){
	Engine::WindowProperties props;

	glfwSystem.reset(new Engine::GLFWSystem);

	glfwSystem->start();

	glfwWindow.reset(new Engine::GLFWWindowImpl(props));
}

GLFW_GL_mock::~GLFW_GL_mock(){
	glfwWindow->close();
	glfwSystem->stop();
}
