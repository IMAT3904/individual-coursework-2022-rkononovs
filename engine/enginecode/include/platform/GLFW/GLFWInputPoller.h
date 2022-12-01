/* \file GLFWInputPoller.h */

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#pragma once

namespace Engine {
	/* \class GLFWInputPoller
	* Input poller for getting current keyboard/mouse state in GLFW system
	*/
	class GLFWInputPoller
	{
	private:
		static GLFWwindow* s_window; //!< Current GLFW window
	public:
		static bool isKeyPressed(int keyCode); //!< Is the key pressed?
		static bool isMouseButtonPressed(int mouseButton); //!< Is the mouse button pressed?
		static glm::vec2 getMousePosition(); //!< Current mouse position
		static void setCurrentWindow(GLFWwindow* newWindow) { s_window = newWindow; } //!< Set current window
	};
}