/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"

namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}
		// Start logger
		m_loggerSystem.reset(new loggerSys);
		m_loggerSystem->start();
		
		// Reset and start timer
		m_timer.reset(new miliTimer);
		m_timer->start();
	}

	Application::~Application()
	{
		//Stop logger
		//m_loggerSystem->stop();
	}


	void Application::run()
	{
		float timestep = 0.f;
		float timeSeconds = 0.f;
		int seconds = 0;
		loggerSys::info("Application is starting.");
		loggerSys::file("Application is starting."); // TODO: FIX BUG WHEN SOMETIMES IT'S NOT LOGGING PROPERLY :(
		while (m_running)
		{
			timestep = m_timer->getElapsedTime();
			timeSeconds += timestep;
			if (timeSeconds >= 1) {
				seconds++;
				loggerSys::trace("{0} seconds elapsed", seconds); // TODO: FIX TIMER THAT INCREMENTS NOT IN SECONDS BUT IN 3 SECONDS :(
				timeSeconds = 0;
			}
			// loggerSys::trace("FPS {0}", 1.0f / timestep);

			m_timer->reset();
		};
	}

}
