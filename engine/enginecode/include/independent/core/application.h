/** \file application.h
*/
#pragma once

#include "systems/loggerSys.h"
#include "core/timer.h"
#include "events/events.h"
#include "core/window.h"
#include "core/inputPoller.h"

namespace Engine {

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?
		// EventHandler m_handler; //!< Event handler 
	protected:
		Application(); //!< Constructor

		std::shared_ptr<LoggerSys> m_loggerSystem; //!< Logger for system logging
		std::shared_ptr<Timer> m_timer; //!< Timer for keeping the time in the engine in milliseconds
		std::shared_ptr<Timer> m_timerSeconds; //!< Timer for keeping the time in engine in seconds
		std::shared_ptr<System> m_windowsSystem; //!< Window system
		std::shared_ptr<Window> m_window; //!< Window
		bool m_updatedView = false;
		bool m_EulerCamera = true;

		bool onClose(WindowCloseEvent& e); //!< Run when the window closes
		bool onResize(WindowResizeEvent& e); //!< Run when the window is resized
		bool onFocus(WindowFocusEvent& e); //!< Run when window is focused
		bool onLostFocus(WindowLostFocusEvent& e); //!< Run when window lost focus
		bool onWindowMoved(WindowMovedEvent& e); //!< Run when window is moved

		bool onKeyPressed(KeyPressedEvent& e); //!< Run when the key is pressed
		bool onKeyReleased(KeyReleasedEvent& e); //!< Run when the key is released
		bool onKeyTyped(KeyTypedEvent& e); //!< Run when the key is typed

		bool onMouseButtonPressed(MouseButtonPressedEvent& e); //!< Run when the mouse button is pressed
		bool onMouseButtonReleased(MouseButtonReleasedEvent& e); //!< Run when the mouse button is released
		bool onMouseMoved(MouseMovedEvent& e); //!< Run when mouse is moved
		bool onMouseScrolled(MouseScrolledEvent& e); //!< Run when mouse is scrolled

	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		inline std::shared_ptr<Window>& getWindow() { return m_window; } //!< Window getter
		void run(); //!< Main loop
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}