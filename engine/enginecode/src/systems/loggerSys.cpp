/** \file loggerSys.cpp */
#include "engine_pch.h"
#include "systems/loggerSys.h"

namespace Engine {
	std::shared_ptr<spdlog::logger> loggerSys::s_consoleLogger = nullptr;

	void Engine::loggerSys::start(SystemSignal init, ...)
	{
		spdlog::set_pattern("%^[%T]: %v%$");
		spdlog::set_level(spdlog::level::trace);

		s_consoleLogger = spdlog::stdout_color_mt("Console");

	}
}
