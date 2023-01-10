/* \file inputPoller.h */

#include <glm/glm.hpp>

#pragma once

namespace Engine {
	/* \class InputPoller 
	* Input poller for getting current keyboard/mouse state
	*/
	class InputPoller
	{
	private:
	public:
		static bool isKeyPressed(int keyCode); //!< Is the key pressed?
		static bool isMouseButtonPressed(int mouseButton); //!< Is the mouse button pressed?
		static glm::vec2 getMousePosition(); //!< Current mouse position
		static void setNativeWindow(void* nativeWindow); //!< Set the native window
		inline static float getMouseX() { return getMousePosition().x; } //!< Get mouse X position
		inline static float getMouseY() { return getMousePosition().y; } //!< Get mouse Y position

	};
}