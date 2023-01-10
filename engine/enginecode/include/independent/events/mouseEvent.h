/** \file mouseEvent.h */
#pragma once

#include "event.h"
#include <glm/glm.hpp>

namespace Engine {

	/** \class MouseEvent
	*\brief base class for mouse events
	*/
	class MouseEvent : public Event {
	public:
		int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; } //!< Get the event category flags
	};

	/** \class MouseMovedEvent
	*\brief interface to handle the mouse moved event
	*/
	class MouseMovedEvent : public MouseEvent {
	private:
		float m_mouseX; //!< Mouse movement in x axis
		float m_mouseY; //!< Mouse movement in y axis
	public:
		MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {} //!< Constructor

		EventType getEventType() const override { return EventType::MouseMoved; } //!< Get the event type

		inline float getX() const { return m_mouseX; } //!< Get X position of the mouse
		inline float getY() const { return m_mouseY; } //!< Get Y position of the mouse
		inline glm::vec2 getPos() const { return glm::vec2(m_mouseX, m_mouseY); } //!< Get X and Y position of the mouse as a vec2
	};

	/** \class MouseScrollEvent
	*\brief interface to handle the mouse scroll event
	*/
	class MouseScrolledEvent : public MouseEvent {
	private:
		float m_xOffset; //!< Scroll in X
		float m_yOffset;//!< Scroll in Y
	public:
		MouseScrolledEvent(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {} //!< Constructor

		EventType getEventType() const override { return EventType::MouseScrolled; } //!< Get the event type

		inline float getXOffset() const { return m_xOffset; } //!< Get X scroll
		inline float getYOffset() const { return m_yOffset; } //!< Get Y scroll
	};

	/** \class MouseButtonPressedEvent
	*\brief interface to handle the mouse button press event
	*/
	class MouseButtonPressedEvent : public MouseEvent {
	private:
		int m_button; //!< Button code
	public:
		MouseButtonPressedEvent(int button) : m_button(button) {} //!< Constructor

		EventType getEventType() const override { return EventType::MouseButtonPressed; } //!< Get the event type

		inline int getButton() const { return m_button; } //!< Get the button code
	};

	/** \class MouseButtonReleasedEvent
	*\brief interface to handle the mouse button released event
	*/
	class MouseButtonReleasedEvent : public MouseEvent {
	private:
		int m_button; //!< Button code
	public:
		MouseButtonReleasedEvent(int button) : m_button(button) {} //!< Constructor

		EventType getEventType() const override { return EventType::MouseButtonReleased; } //!< Get the event type

		inline int getButton() const { return m_button; } //!< Get the button code
	};
}