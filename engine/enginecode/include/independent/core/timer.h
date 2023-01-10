/** \file timer.h */
#pragma once
#include <chrono>

namespace Engine {
	/**
	\class Timer
	Class that provides time keeping for engine
	*/

	class Timer {
	public:
		virtual void start() = 0; //!< Starting the timer
		virtual void reset() = 0; //!< Reset the timer
		virtual float getElapsedTime() = 0; //!< Get the time elapsed since start of the timer in 
	};

	/**
	\class MiliTimer
	Class that provides millisecond time keeping for the engine
	*/

	class MiliTimer : public Timer {
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime; //!< Starting time of the timer
		std::chrono::time_point<std::chrono::high_resolution_clock> m_endTime; //!< Ending time of the timer
	public:
		inline void start() override { m_startTime = std::chrono::high_resolution_clock::now(); } //!< Start the timer
		inline void reset() override { m_startTime = std::chrono::high_resolution_clock::now(); } //!< End the timer

		float getElapsedTime() {
			m_endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float, std::milli> elapsed = m_endTime - m_startTime;

			return elapsed.count() / 1000.f;
		} //!< Calculate elapsed time
	};

	/**
	\class SecondsTimer
	Class that provides seconds time keeping for the engine
	*/

	class SecondsTimer : public Timer {
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime; //!< Starting time of the timer
		std::chrono::time_point<std::chrono::high_resolution_clock> m_endTime; //!< Ending time of the timer
	public:
		inline void start() override { m_startTime = std::chrono::high_resolution_clock::now(); } //!< Start the timer
		inline void reset() override { m_startTime = std::chrono::high_resolution_clock::now(); } //!< End the timer

		float getElapsedTime() {
			m_endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> elapsed = m_endTime - m_startTime;

			return elapsed.count();
		} //!< Calculate elapsed time
	};
}