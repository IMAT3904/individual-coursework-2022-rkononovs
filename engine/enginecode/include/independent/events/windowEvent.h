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

	class WindowFocusEvent : public Event {
	public:
		WindowFocusEvent() {}
		
		EventType getEventType() const override { return EventType::WindowFocus; } //!< Get the event type
		int getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags
	};

	class WindowLostFocusEvent : public Event {
	public:
		WindowLostFocusEvent() {}

		EventType getEventType() const override { return EventType::WindowLostFocus; } //!< Get the event type
		int getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags
	};

	class WindowMovedEvent : public Event {
	private:
		int m_xPos;
		int m_yPos;
	public:
		WindowMovedEvent(int x, int y) : m_xPos(x), m_yPos(y) {}

		EventType getEventType() const override { return EventType::WindowMoved; } //!< Get the event type
		int getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags

		inline int getXPos() const { return m_xPos; }
		inline int getYPos() const { return m_yPos; }
		inline glm::ivec2 getPos() const { return { m_xPos, m_yPos }; }
	};
}