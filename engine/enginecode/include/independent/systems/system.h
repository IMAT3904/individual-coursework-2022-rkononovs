/** \file system.h
*/

#pragma once

#include <cstdarg>

/**
\class Interface class for all systems
*/

namespace Engine {

	enum class SystemSignal { None = 0 };

	class System
	{
	public:
		virtual ~System() {};
		virtual void start(SystemSignal init = SystemSignal::None, ...) = 0; //!< Start the system
		virtual void stop(SystemSignal close = SystemSignal::None, ...) = 0; //!< Stop the system
	};
}
