/* \file window.h */
#pragma once

#include "events/eventHandler.h"
namespace Engine {
	/** \class Window
	* Abstract window base class.
	*/

	struct WindowProperties {
		char* title;
		unsigned int width;
		unsigned int height;
		bool isFullScreen;
		bool isVSync;

		WindowProperties(char* title = "My Window", unsigned int width = 800, unsigned int height = 600, bool fullscreen = false) : title(title), width(width), height(height), isFullScreen(fullscreen) {}
	};

	class Window {
	protected:
		EventHandler m_handler; //!< Event Handler
		//std::shared_ptr<GraphicsContext> m_context;
	public:
		virtual void init(const WindowProperties& properties) = 0;
		virtual void close() = 0;

		virtual ~Window() {};

		virtual void onUpdate(float timestep) = 0;
		virtual void onResize(unsigned int width, unsigned int height) = 0;
		virtual void setVSync(bool Vsync) = 0;
		virtual void setEventCallback(const std::function<void(Event&)>& callback) = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void* getNativeWindow() const = 0;

		virtual bool isFullScreenMode() const = 0;
		virtual bool isVsync() const = 0;

		inline EventHandler& getEventHandler() { return m_handler; }

		static Window* create(const WindowProperties& properties = WindowProperties());
	};
}