/* \file window.h */
#pragma once

#include "events/eventHandler.h"
#include "core/graphicsContext.h"
namespace Engine {
	/** \struct WindowPropeties
	*\brief common properties for windows defined when creating a GLFW window
	\param title char - title of the window
	\param width uint32_t - width of the window
	\param height uint32_t - height of the window
	\param isFullScreen bool - is the window in fullscreen
	\param isVSync - is the vsync on
	*/
	struct WindowProperties {
		char* title; //!< window title
		unsigned int width; //!< width of window
		unsigned int height; //!< height of window
		bool isFullScreen; //!< is window fullscreen
		bool isVSync; //!< is Vsync on

		WindowProperties(char* title = "My Window", unsigned int width = 800, unsigned int height = 600, bool fullscreen = false) : title(title), width(width), height(height), isFullScreen(fullscreen) {} //!< define default window properties
	};
	/** \class Window
	* Abstract window base class.
	*/
	class Window {
	protected:
		EventHandler m_handler; //!< Event Handler
		std::shared_ptr<GraphicsContext> m_graphicsContext; //!< Graphics context for the window
	public:
		virtual void init(const WindowProperties& properties) = 0; //!< Initialise the window
		virtual void close() = 0; //!< Close the window 

		virtual ~Window() {}; //!< Default destructor class

		virtual void onUpdate(float timestep) = 0; //!< Update the window
		virtual void onResize(unsigned int width, unsigned int height) = 0; //!< Resize the window
		virtual void setVSync(bool Vsync) = 0; //!< Set Vsync of the window 
		virtual void setEventCallback(const std::function<void(Event&)>& callback) = 0; //!< set event callback from the window

		virtual unsigned int getWidth() const = 0; //!< Get width of the window
		virtual unsigned int getHeight() const = 0; //!< Get height of the window

		virtual void* getNativeWindow() const = 0; //!< Get window platform

		virtual bool isFullScreenMode() const = 0; //!< Get window fullscreen status
		virtual bool isVsync() const = 0; //!< Get window vSync status

		inline EventHandler& getEventHandler() { return m_handler; } //!< Get event handler from the window

		static Window* create(const WindowProperties& properties = WindowProperties()); //!< Create window with properties
	};
}