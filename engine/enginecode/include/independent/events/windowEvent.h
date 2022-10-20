/* \file windowEvent.h */
#pragma once

#include "event.h"
#include <glm/glm.hpp>

namespace Engine {
	class WindowCloseEvent : public Event{
	public:
		WindowCloseEvent() {}

		EventType getEventType() const override { return EventType::WindowClose; } //!< Get the event type
		int getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags
	};
	
	class WindowResizeEvent : public Event {
	private:
		int m_width;
		int m_height;
	public:
		WindowResizeEvent(int width, int height) : m_width(width), m_height(height) {}
		
		EventType getEventType() const override { return EventType::WindowResize; } //!< Get the event type
		int getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags

		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }
	};
}