/* \file GLFWWindowImpl.cpp*/

#include "engine_pch.h"
#include "platform/GLFW/GLFWWindowImpl.h"

namespace Engine {

#ifdef NG_PLATFORM_WINDOWS
	Window* Window::create(const WindowProperties& properties = WindowProperties()) {
		return new GLFWWindowImpl(properties);
	}
#endif
	GLFWindowImpl::GLFWindowImpl(const WindowProperties& properties)
	{
		init(properties);
	}
	void GLFWindowImpl::init(const WindowProperties& properties){
	}

	void GLFWindowImpl::close(){
	}

	void GLFWindowImpl::onUpdate(float timestep){
	}

	void GLFWindowImpl::onResize(unsigned int width, unsigned int height){
	}

	void GLFWindowImpl::setVSync(bool Vsync){
	}

	void GLFWindowImpl::setEventCallback(const std::function<void(Event&)>& callback){
	}
}