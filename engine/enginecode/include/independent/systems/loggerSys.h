/** \file LoggerSys.h */
#pragma once
#include "system.h"
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Engine {
	class LoggerSys : public System {
	private:
		static std::shared_ptr<spdlog::logger> s_consoleLogger;
		static std::shared_ptr<spdlog::logger> s_fileLogger;
	public:
		void start(SystemSignal init = SystemSignal::None, ...); //!< Start the logger
		void stop(SystemSignal close = SystemSignal::None, ...) {}; //!< Stop the logger


		template<class ...Args>
		static void info(Args&&... args); //!< Information level logging
		template<class ...Args>
		static void warn(Args&&... args); //!< Warning level logging
		template<class ...Args>
		static void error(Args&&... args); //!< Error level logging
		template<class ...Args>
		static void trace(Args&&... args); //!< Trace level logging
		template<class ...Args>
		static void debug(Args&&... args); //!< Debugging level logging
		template<class ...Args>
		static void file(Args&&... args); //!< Debugging level logging
	};

	template<class ...Args>
	static void LoggerSys::info(Args&&... args) {
		s_consoleLogger->info(std::forward<Args>(args) ...);
	}

	template<class ...Args>
	static void LoggerSys::warn(Args&&... args) {
		s_consoleLogger->warn(std::forward<Args>(args) ...);
	}

	template<class ...Args>
	static void LoggerSys::error(Args&&... args) {
		s_consoleLogger->error(std::forward<Args>(args) ...);
	}

	template<class ...Args>
	static void LoggerSys::trace(Args&&... args) {
		s_consoleLogger->trace(std::forward<Args>(args) ...);
	}

	template<class ...Args>
	static void LoggerSys::debug(Args&&... args) {
		s_consoleLogger->debug(std::forward<Args>(args) ...);
	}

	template<class ...Args>
	static void LoggerSys::file(Args&&... args) {
		if (s_fileLogger) s_fileLogger->info(std::forward<Args>(args) ...); s_fileLogger->flush();
	}
}