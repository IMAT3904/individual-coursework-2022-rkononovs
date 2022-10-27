/** \file GLFWWindowImpl.h */
#pragma once

#include "core/window.h"
#include <GLFW/glfw3.h>

	/** \class GLFWwindowImpl
	* Implementation of a window using GLFW
	*/
namespace Engine {
	class GLFWindowImpl : public Window {
	private:
		WindowProperties m_props; //!< Properties of the window
		GLFWwindow* m_native; //!< Native GLFW window
	public:
		GLFWindowImpl(const WindowProperties& properties); //!< Constructor 
		
		virtual void init(const WindowProperties& properties) override; //!< Initialise the window
		virtual void close() override; //!< Close the window

		//virtual ~Window() {};

		virtual void onUpdate(float timestep) override;
		virtual void onResize(unsigned int width, unsigned int height) override;
		virtual void setVSync(bool Vsync) override;
		virtual void setEventCallback(const std::function<void(Event&)>& callback) override;

		virtual inline unsigned int getWidth() const override { return m_props.width; };
		virtual inline unsigned int getHeight() const override { return m_props.height; };

		virtual inline void* getNativeWidnow() const override { return m_native; };

		virtual inline bool isFullScreenMode() const override { return m_props.isFullScreen; };
		virtual inline bool isVsync() const override { return m_props.isVSync; };

		static Window* create(const WindowProperties& propertie = WindowProperties());
	};
}