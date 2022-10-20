/** \file timer.h */
#pragma once
#include <chrono>

namespace Engine {
	/**
	\class Timer
	Class that provides time keeping for engine
	*/

	class timer {
	public:
		virtual void start() = 0; //!< Starting the timer
		virtual void reset() = 0; //!< Reset the timer
		virtual float getElapsedMiliTime() = 0; //!< Get the time elapsed since start of the timer in 
		virtual float getElapsedSeconds() = 0;
	};

	/**
	\class Timer
	Class that provides millisecond time keeping for the engine
	*/

	class miliTimer : public timer {
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_endTime;
	public:
		inline void start() override { m_startTime = std::chrono::high_resolution_clock::now(); }
		inline void reset() override { m_startTime = std::chrono::high_resolution_clock::now(); }

		float getElapsedMiliTime() {
			m_endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float, std::milli> elapsed = m_endTime - m_startTime;

			return elapsed.count() / 1000.f;
		}
		
		float getElapsedSeconds() {
			m_endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> elapsed = m_endTime - m_startTime;

			return elapsed.count();
		}
	};
}