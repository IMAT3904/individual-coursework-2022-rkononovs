/** \file application.h
*/
#pragma once

#include "systems/loggerSys.h"
#include "core/timer.h"

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
	protected:
		Application(); //!< Constructor

		std::shared_ptr<loggerSys> m_loggerSystem; //!< Logger for system logging
		std::shared_ptr<timer> m_timer; //!< Timer for keeping the time in the engine
	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}