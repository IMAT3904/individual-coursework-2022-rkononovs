/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"

#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWSystem.h"
#endif

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
		m_loggerSystem.reset(new LoggerSys);
		m_loggerSystem->start();
		
		// Reset and start timer
		m_timer.reset(new MiliTimer);
		m_timerSeconds.reset(new SecondsTimer);

		m_timerSeconds->start();
		m_timer->start();

		// Start the windows system
#ifdef NG_PLATFORM_WINDOWS
		m_windowsSystem.reset(new GLFWSystem);
#endif
		m_windowsSystem->start();

		WindowProperties props("My Game Engine", 1044, 800);
		m_window.reset(Window::create(props));

		m_handler.setOnCloseCallback(std::bind(&Application::onClose, this, std::placeholders::_1));
	}

	bool Application::onClose(WindowCloseEvent& e)
	{
		e.handle(true);
		m_running = false;
		return e.handled();
	}

	Application::~Application()
	{
		// Stop logger
		//m_loggerSystem->stop();
		// Stop window system
		m_windowsSystem->stop();
	}


	void Application::run()
	{
		float timestep = 0.f;
		float timeSeconds = 0.f;
		int seconds = 0;
		LoggerSys::info("Application is starting.");
		LoggerSys::file("Application is starting. One");
		LoggerSys::file("Application is starting. Two");
		while (m_running)
		{
			timestep = m_timer->getElapsedTime();
			m_timer->reset();
			timeSeconds = m_timerSeconds->getElapsedTime();


			if (timeSeconds >= 1) { // Check if second passed, if yes output how many seconds passed in total.
				seconds++;
				LoggerSys::trace("{0} seconds elapsed", seconds);
				LoggerSys::trace("FPS {0}", 1.0f / timestep);
				timeSeconds = 0;
				m_timerSeconds->reset();
			}

			if (seconds > 5) {
				WindowResizeEvent resize(800, 600);
			}


			if (seconds > 8) {
				WindowCloseEvent close;

				auto& callback = m_handler.getOnCloseFunction();
				callback(close);
			}
		};
	}

}
