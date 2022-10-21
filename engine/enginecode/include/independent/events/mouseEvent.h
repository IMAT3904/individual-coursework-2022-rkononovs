#pragma once

#include "event.h"
#include <glm/glm.hpp>

namespace Engine {
	class MouseEvent : public Event {
		int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; } //!< Get the event category flags
	};

	class MouseMovedEvent : public MouseEvent {
	private:
		float m_mouseX;
		float m_mouseY;
	public:
		MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(x) {}

		EventType getEventType() const override { return EventType::MouseMoved; } //!< Get the event type
		// int getCategoryFlags() const override { return EventCategoryMouse; } //!< Get the event category flags

		inline float getX() const { return m_mouseX; }
		inline float getY() const { return m_mouseY; }
		inline glm::vec2 getPos() const { return glm::vec2(m_mouseX, m_mouseY); }
	};

	class MouseScrolledEvent : public MouseEvent {
	private:
		float m_xOffset;
		float m_yOffset;
	public:
		MouseScrolledEvent(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}

		EventType getEventType() const override { return EventType::MouseScrolled; } //!< Get the event type
		// int getCategoryFlags() const override { return EventCategoryMouse; } //!< Get the event category flags

		inline float getXOffset() const { return m_xOffset; }
		inline float getYOffset() const { return m_yOffset; }
	};

	class MouseButtonPressedEvent : public MouseEvent {
	private:
		int m_button; // Why is it INT ? Maybe later change to bool
	public:
		MouseButtonPressedEvent(int button) : m_button(button) {}

		EventType getEventType() const override { return EventType::MouseButtonPressed; } //!< Get the event type
		// int getCategoryFlags() const override { return EventCategoryInput; } //!< Get the event category flags

		inline int getButton() const { return m_button; }
	};

	class MouseButtonReleasedEvent : public MouseEvent {
	private:
		int m_button; // Why is it INT ? Maybe later change to bool
	public:
		MouseButtonReleasedEvent(int button) : m_button(button) {}

		EventType getEventType() const override { return EventType::MouseButtonReleased; } //!< Get the event type
		// int getCategoryFlags() const override { return EventCategoryInput; } //!< Get the event category flags

		inline int getButton() const { return m_button; }
	};
}