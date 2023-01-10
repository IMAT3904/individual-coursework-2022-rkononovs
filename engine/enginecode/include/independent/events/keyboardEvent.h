/** \file keyboardEvent.h */
#pragma once

#include "event.h"

namespace Engine {
	/** \class KeyPressedEvent
	*\brief interface to handle the key pressed event
	*/
	class KeyPressedEvent : public Event {
	private:
		int m_repeatCount; //!< Key repeat count
		int m_keyCode;//!< Key code for the key pressed
	public:
		KeyPressedEvent(int keyCode, int repeatCount) : m_keyCode(keyCode), m_repeatCount(repeatCount) {} //!< Constructor

		EventType getEventType() const override { return EventType::KeyPressed; } //!< Get the event type
		int getCategoryFlags() const override { return EventCategoryKeyboard; } //!< Get the event category flags

		inline int getKeyCode() const { return m_keyCode; } //!< Get the key code
		inline int getRepeatCount() const { return m_repeatCount; } //!< Get the repeat count
	};

	/** \class KeyReleasedEvent
	*\brief interface to handle the key released event
	*/
	class KeyReleasedEvent : public Event {
	private:
		int m_keyCode; //!< Key code for the key pressed
	public:
		KeyReleasedEvent(int keyCode) : m_keyCode(keyCode) {} //!< Constructor

		EventType getEventType() const override { return EventType::KeyReleased; } //!< Get the event type
		int getCategoryFlags() const override { return EventCategoryKeyboard; } //!< Get the event category flags

		inline int getKeyCode() const { return m_keyCode; } //!< Get the key code
	};

	/** \class KeyTypedEvent
	*\brief interface to handle the key typed event
	*/
	class KeyTypedEvent : public Event {
	private:
		int m_repeatCount; //!< Key repeat count
		int m_keyCode; //!< Key code for the key pressed
	public:
		KeyTypedEvent(int keyCode, int repeatCount) : m_keyCode(keyCode), m_repeatCount(repeatCount) {} //!< Constructor

		EventType getEventType() const override { return EventType::KeyType; } //!< Get the event type
		int getCategoryFlags() const override { return EventCategoryKeyboard; } //!< Get the event category flags

		inline int getKeyCode() const { return m_keyCode; } //!< Get the key code
		inline int getRepeatCount() const { return m_repeatCount; } //!< Get the repeat count
	};
}