/* \file GLFWInputPoller.cpp */

#include "engine_pch.h"
#include "platform/GlFW/GLFWInputPoller.h"

namespace Engine{


	GLFWwindow* GLFWInputPoller::s_window = nullptr;

	bool GLFWInputPoller::isKeyPressed(int keyCode) // Check if key is pressed
	{
		if (s_window) {
			auto answer = glfwGetKey(s_window, keyCode);
			return answer == GLFW_PRESS || answer == GLFW_REPEAT;
		}
		return false;
	}
	bool GLFWInputPoller::isMouseButtonPressed(int mouseButton) // Check if mouse button pressed
	{
		if (s_window) {
			auto answer = glfwGetMouseButton(s_window, mouseButton);
			return answer == GLFW_PRESS;
		}
		return false;
	}
	glm::vec2 GLFWInputPoller::getMousePosition() // Retrieve mouse position
	{
		if (s_window) {
			double x, y;
			glfwGetCursorPos(s_window, &x, &y);
			return glm::vec2(static_cast<float>(x), static_cast<float>(y));
		}
		return { -1.f, 1.f };
	}
}