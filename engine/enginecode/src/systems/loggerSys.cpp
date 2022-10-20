/** \file LoggerSys.cpp */
#include "engine_pch.h"
#include "systems/loggerSys.h"
#include <direct.h>

namespace Engine {
	std::shared_ptr<spdlog::logger> LoggerSys::s_consoleLogger = nullptr;
	std::shared_ptr<spdlog::logger> LoggerSys::s_fileLogger = nullptr;

	void Engine::LoggerSys::start(SystemSignal init, ...)
	{
		spdlog::set_pattern("%^[%T]: %v%$");
		spdlog::set_level(spdlog::level::trace);

		s_consoleLogger = spdlog::stdout_color_mt("Console");

		char filepath[256] = "logs/";
		char time[128];

		try {
			mkdir(filepath);
			std::time_t t = std::time(nullptr);
			std::strftime(time, sizeof(time), "%d_%m_%y %I_%M_%S", std::localtime(&t));
			strcat_s(filepath, time);
			strcat_s(filepath, ".txt");
			s_fileLogger = spdlog::basic_logger_mt("file", filepath);
		}
		catch (const spdlog::spdlog_ex& e) {
			s_consoleLogger->error("Could not start file logger: {0}", e.what());
			s_fileLogger.reset();
		}
		//catch (std::exception& e) {
		//	s_consoleLogger->error("Uncalled error");
		//}
	}
}
