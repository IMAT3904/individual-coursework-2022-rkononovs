/** \file GLFWSystem.h */
#pragma once

#include "systems/system.h"
#include "systems/loggerSys.h"

#include <GLFW/glfw3.h>

namespace Engine {
	class GLFWSystem : public System {
		virtual void start(SystemSignal init = SystemSignal::None, ...) override { //!< Start the GLFW System
			auto errorCode = glfwInit();
			if (!errorCode) {
			LoggerSys::error("Cannot start GLFW: {0}", errorCode);
			}
		}
		virtual void stop(SystemSignal close = SystemSignal::None, ...) override { //!< Stop the GLFW System
			glfwTerminate();
		}
	};
}