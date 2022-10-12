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
	}

	Application::~Application()
	{
	}


	void Application::run()
	{
		while (m_running)
		{

		};
	}

}
