/** \file windowEvent.h */
#pragma once

#include "event.h"
#include <glm/glm.hpp>

namespace Engine {

	/** \class WindowCloseEvent
	*\brief interface to handle the window close event
	*/
	class WindowCloseEvent : public Event{
	public:
		WindowCloseEvent() {} //!< Constructor

		EventType getEventType() const override { return EventType::WindowClose; } //!< Get the event type
		int getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags
	};
	
	/** \class WindowResizeEvent
	*\brief interface to handle the window resize event
	*/
	class WindowResizeEvent : public Event {
	private:
		int m_width; //!< Window width after resize
		int m_height; //!< Window height after resize
	public:
		WindowResizeEvent(int width, int height) : m_width(width), m_height(height) {}  //!< Constructor
		
		EventType getEventType() const override { return EventType::WindowResize; } //!< Get the event type
		int getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags

		inline int getWidth() const { return m_width; } //!< Get resized window width
		inline int getHeight() const { return m_height; } //!< Get resized window height
	};

	/** \class WindowFocusEvent
	*\brief interface to handle the window focus event
	*/
	class WindowFocusEvent : public Event {
	public:
		WindowFocusEvent() {} //!< Constructor
		
		EventType getEventType() const override { return EventType::WindowFocus; } //!< Get the event type
		int getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags
	};

	/** \class WindowLostFocusEvent
	*\brief interface to handle the window lost focus event
	*/
	class WindowLostFocusEvent : public Event {
	public:
		WindowLostFocusEvent() {} //!< Constructor

		EventType getEventType() const override { return EventType::WindowLostFocus; } //!< Get the event type
		int getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags
	};

	/** \class WindowMovedEvent
	*\brief interface to handle the window moved event 
	*/
	class WindowMovedEvent : public Event {
	private:
		int m_xPos; //!< New X position after window moved
		int m_yPos; //!< New Y position after window moved
	public:
		WindowMovedEvent(int x, int y) : m_xPos(x), m_yPos(y) {} //!< Constructor

		EventType getEventType() const override { return EventType::WindowMoved; } //!< Get the event type
		int getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags

		inline int getXPos() const { return m_xPos; } //!< Get the moved window x position
		inline int getYPos() const { return m_yPos; } //!< Get the moved window y positon
		inline glm::ivec2 getPos() const { return { m_xPos, m_yPos }; } //!< Get the moved window x and y position
	};
}