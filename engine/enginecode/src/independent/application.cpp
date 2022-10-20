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

		m_timerSeconds.reset(new secondsTimer);
		m_timerSeconds->start();
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
		loggerSys::file("Application is starting. One");
		loggerSys::file("Application is starting. Two");
		while (m_running)
		{
			timestep = m_timer->getElapsedTime();
			m_timer->reset();
			timeSeconds = m_timerSeconds->getElapsedTime();


			if (timeSeconds >= 1) { // Check if second passed, if yes output how many seconds passed in total.
				seconds++;
				loggerSys::trace("{0} seconds elapsed", seconds);
				timeSeconds = 0;
				m_timerSeconds->reset();
			}
			// loggerSys::trace("FPS {0}", 1.0f / timestep);
		};
	}

}
