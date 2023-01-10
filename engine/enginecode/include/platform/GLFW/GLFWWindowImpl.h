/** \file GLFWWindowImpl.h */
#pragma once

#include "core/window.h"
#include <GLFW/glfw3.h>

	/** \class GLFWWindowImpl
	* Implementation of a window using GLFW
	*/
namespace Engine {
	class GLFWWindowImpl : public Window {
	private:
		WindowProperties m_props; //!< Properties of the window
		GLFWwindow* m_native; //!< Native GLFW window
		float m_aspectRation; //!< Windows aspect ratio
	public:
		GLFWWindowImpl(const WindowProperties& properties); //!< Constructor 
		
		virtual void init(const WindowProperties& properties) override; //!< Initialise the window
		virtual void close() override; //!< Close the window

		virtual void onUpdate(float timestep) override; //!< Updates the logic while window is open
		virtual void onResize(unsigned int width, unsigned int height) override; //!< Callback that fires  while window is being resized
		virtual void setVSync(bool Vsync) override; //!< Set vSync
		virtual void setEventCallback(const std::function<void(Event&)>& callback) override; //!< Set event callback

		virtual inline unsigned int getWidth() const override { return m_props.width; }; //!< Get window width
		virtual inline unsigned int getHeight() const override { return m_props.height; }; //!< Get window height

		virtual inline void* getNativeWindow() const override { return m_native; }; //!< Get window native size

		virtual inline bool isFullScreenMode() const override { return m_props.isFullScreen; }; //!< Is window in fullscreen mode?
		virtual inline bool isVsync() const override { return m_props.isVSync; }; //!< Is vSync on?
	};
}