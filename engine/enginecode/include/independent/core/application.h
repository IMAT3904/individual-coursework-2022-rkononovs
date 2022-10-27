/** \file application.h
*/
#pragma once

#include "systems/loggerSys.h"
#include "core/timer.h"
#include "events/events.h"
#include "events/eventHandler.h"

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
		EventHandler m_handler; //!< Event handler 
	protected:
		Application(); //!< Constructor

		std::shared_ptr<LoggerSys> m_loggerSystem; //!< Logger for system logging
		std::shared_ptr<Timer> m_timer; //!< Timer for keeping the time in the engine in milliseconds
		std::shared_ptr<Timer> m_timerSeconds; //!< Timer for keeping the time in engine in seconds
		std::shared_ptr<System> m_windowsSystem; //!< Window system

		bool onClose(WindowCloseEvent& e);
	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}