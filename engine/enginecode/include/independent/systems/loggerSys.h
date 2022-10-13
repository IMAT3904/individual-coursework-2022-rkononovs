/** \file loggerSys.h */
#pragma once
#include "system.h"
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Engine {
	class loggerSys : public System {
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
	static void loggerSys::info(Args&&... args) {
		s_consoleLogger->info(std::forward<Args>(args) ...);
	}

	template<class ...Args>
	static void loggerSys::warn(Args&&... args) {
		s_consoleLogger->warn(std::forward<Args>(args) ...);
	}

	template<class ...Args>
	static void loggerSys::error(Args&&... args) {
		s_consoleLogger->error(std::forward<Args>(args) ...);
	}

	template<class ...Args>
	static void loggerSys::trace(Args&&... args) {
		s_consoleLogger->trace(std::forward<Args>(args) ...);
	}

	template<class ...Args>
	static void loggerSys::debug(Args&&... args) {
		s_consoleLogger->debug(std::forward<Args>(args) ...);
	}

	template<class ...Args>
	static void loggerSys::file(Args&&... args) {
		if(s_fileLogger) s_fileLogger->trace(std::forward<Args>(args) ...);
	}
}