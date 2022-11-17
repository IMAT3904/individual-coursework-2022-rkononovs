/* \file keyboardEvent.h */
#pragma once

#include "event.h"

namespace Engine {
	class KeyPressedEvent : public Event {
	private:
		int m_repeatCount;
		int m_keyCode;
	public:
		KeyPressedEvent(int keyCode, int repeatCount) : m_keyCode(keyCode), m_repeatCount(repeatCount) {}

		EventType getEventType() const override { return EventType::KeyPressed; } //!< Get the event type
		int getCategoryFlags() const override { return EventCategoryKeyboard; } //!< Get the event category flags

		inline int getKeyCode() const { return m_keyCode; }
		inline int getRepeatCount() const { return m_repeatCount; }

	};

	class KeyReleasedEvent : public Event {
	private:
		// int m_repeatCount;
		int m_keyCode;
	public:
		KeyReleasedEvent(int keyCode) : m_keyCode(keyCode) {} // m_repeatCount(repeatCount) {}

		EventType getEventType() const override { return EventType::KeyReleased; } //!< Get the event type
		int getCategoryFlags() const override { return EventCategoryKeyboard; } //!< Get the event category flags

		inline int getKeyCode() const { return m_keyCode; }
		// inline int getRepeatCount() const { return m_repeatCount; }

	};

	class KeyTypedEvent : public Event {
	private:
		int m_repeatCount;
		int m_keyCode;
	public:
		KeyTypedEvent(int keyCode, int repeatCount) : m_keyCode(keyCode), m_repeatCount(repeatCount) {}

		EventType getEventType() const override { return EventType::KeyType; } //!< Get the event type
		int getCategoryFlags() const override { return EventCategoryKeyboard; } //!< Get the event category flags

		inline int getKeyCode() const { return m_keyCode; }
		inline int getRepeatCount() const { return m_repeatCount; }

	};
}