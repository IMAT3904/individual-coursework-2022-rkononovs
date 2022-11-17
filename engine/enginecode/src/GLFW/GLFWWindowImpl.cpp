/* \file GLFWWindowImpl.cpp*/

#include "engine_pch.h"
#include "platform/GLFW/GLFWWindowImpl.h"
#include "systems/loggerSys.h"

namespace Engine {

#ifdef NG_PLATFORM_WINDOWS
	Window* Window::create(const WindowProperties& properties) {
		return new GLFWWindowImpl(properties);
	}
#endif
	GLFWWindowImpl::GLFWWindowImpl(const WindowProperties& properties)
	{
		init(properties);
	}
	void GLFWWindowImpl::init(const WindowProperties& properties){
		m_props = properties;
		m_aspectRation = static_cast<float>(m_props.width) / static_cast<float>(m_props.height);

		if (m_props.isFullScreen) {
			LoggerSys::error("Fullscreen not implemented");
		}
		else {
			m_native = glfwCreateWindow(m_props.width, m_props.height, m_props.title, nullptr, nullptr);
		}
	}

	void GLFWWindowImpl::close(){
		glfwDestroyWindow(m_native);
	}

	void GLFWWindowImpl::onUpdate(float timestep){
		glfwPollEvents();
	}

	void GLFWWindowImpl::onResize(unsigned int width, unsigned int height){
	}

	void GLFWWindowImpl::setVSync(bool VSync){
		m_props.isVSync = VSync;
		if (VSync) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
	}

	void GLFWWindowImpl::setEventCallback(const std::function<void(Event&)>& callback){
	}
}