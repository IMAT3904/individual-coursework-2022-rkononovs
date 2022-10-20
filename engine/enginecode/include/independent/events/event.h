/* \file event.h */
#pragma once


namespace Engine {
	/** \enum EventType  
	* An enum for event types */

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyType,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/** \enum EventCategory
	* Enum for type category flags
	*/

	enum EventCategory {
		None = 0,
		EventCategoryWindow = 1 << 0,			// 00000001
		EventCategoryInput = 1 << 1,			// 00000010
		EventCategoryKeyboard = 1 << 2,         // 00000100
		EventCategoryMouse = 1 << 3,            // 00001000
		EventCategoryMouseButton = 1 << 4       // 00010000
	};

	/**
	* \class Event
	* Event base class
	*/

	class Event {
	private:
		bool m_handled = false; //!< Has the event been handled
	public:
		virtual EventType getEventType() const = 0; //!< Get the event type
		virtual int getCategoryFlags() const = 0; //!< Get the event category flag
		inline bool handled() const { return m_handled; } //!< Return has the event been handled
		inline void handle(bool isHandled) { m_handled = isHandled; } //!< Handle the event
		inline bool isInCategory(EventCategory category) { return getCategoryFlags() & category; } //!< Is the event in category?
	};

}
