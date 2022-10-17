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
		//Start logger
		m_loggerSystem.reset(new loggerSys);
		m_loggerSystem->start();
	}

	Application::~Application()
	{
		//Stop logger
		//m_loggerSystem->stop();
	}


	void Application::run()
	{
		loggerSys::info("Application is starting.");
		//loggerSys::file("Testing.");
		loggerSys::file("Application is starting."); // TODO: FIX BUG WHEN SOMETIMES IT'S NOT LOGGING PROPERLY :(
		//loggerSys::file("Testing.");
		while (m_running)
		{
			//loggerSys::file("Testing.");
		};
	}

}
