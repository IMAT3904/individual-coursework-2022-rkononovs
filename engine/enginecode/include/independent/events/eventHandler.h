/** \file eventHandler.h*/
#pragma once

#include "events.h"
#include <functional>

namespace Engine {
	/** \class EventHandler
	* \brief class for handling events
	*/
	class EventHandler {
	private:
		// Window events
		std::function<bool(WindowCloseEvent&)> m_onCloseFunction = std::bind(&EventHandler::defaultOnClose, this, std::placeholders::_1); //!< Bind the window on close function to make it callable
		std::function<bool(WindowResizeEvent&)> m_onResizeFunction = std::bind(&EventHandler::defaultOnResize, this, std::placeholders::_1); //!< Bind the window on resize function to make it callable
		std::function<bool(WindowFocusEvent&)> m_onFocusFunction = std::bind(&EventHandler::defaultOnFocus, this, std::placeholders::_1); //!< Bind the window on focus function to make it callable
		std::function<bool(WindowLostFocusEvent&)> m_onLostFocusFunction = std::bind(&EventHandler::defaultOnLostFocus, this, std::placeholders::_1); //!< Bind the window on lost focus function to make it callable
		std::function<bool(WindowMovedEvent&)> m_onMovedFunction = std::bind(&EventHandler::defaultOnWindowMoved, this, std::placeholders::_1); //!< Bind the window on moved function to make it callable

		// Keyboard events
		std::function<bool(KeyPressedEvent&)> m_onKeyPressedFunction = std::bind(&EventHandler::defaultOnKeyPress, this, std::placeholders::_1); //!< Bind the key on pressed function to make it callable
		std::function<bool(KeyReleasedEvent&)> m_onKeyReleasedFunction = std::bind(&EventHandler::defaultOnKeyRelease, this, std::placeholders::_1); //!< Bind the key on released function to make it callable
		std::function<bool(KeyTypedEvent&)> m_onKeyTypedFunction = std::bind(&EventHandler::defaultOnKeyTyped, this, std::placeholders::_1); //!< Bind the key on typed function to make it callable

		// Mouse events
		std::function<bool(MouseButtonPressedEvent&)> m_onMouseDownFunction = std::bind(&EventHandler::defaultOnMouseDown, this, std::placeholders::_1); //!< Bind the mouse on pressed function to make it callable
		std::function<bool(MouseButtonReleasedEvent&)> m_onMouseUpFunction = std::bind(&EventHandler::defaultOnMouseUp, this, std::placeholders::_1); //!< Bind the mouse on released function to make it callable
		std::function<bool(MouseMovedEvent&)> m_onMouseMovedFunction = std::bind(&EventHandler::defaultOnMouseMoved, this, std::placeholders::_1); //!< Bind the mouse on moved function to make it callable
		std::function<bool(MouseScrolledEvent&)> m_onMouseWheelFunction = std::bind(&EventHandler::defaultOnMouseWheel, this, std::placeholders::_1); //!< Bind the mouse on scrolled function to make it callable

		// Window bool callbacks
		bool defaultOnClose(WindowCloseEvent&) { return false; } //!< Return Window close event false when not event handled
		bool defaultOnResize(WindowResizeEvent&) { return false; } //!< Return Window resize event false when not event handled
		bool defaultOnFocus(WindowFocusEvent&) { return false; } //!< Return Window focus event false when not event handled
		bool defaultOnLostFocus(WindowLostFocusEvent&) { return false; } //!< Return Window lost focus event false when not event handled
		bool defaultOnWindowMoved(WindowMovedEvent&) { return false; } //!< Return Window moved event false when not event handled

		// Keyboard bool callbacks
		bool defaultOnKeyPress(KeyPressedEvent&) { return false; } //!< Return key pressed event false when not event handled
		bool defaultOnKeyRelease(KeyReleasedEvent&) { return false; } //!< Return key released event false when not event handled
		bool defaultOnKeyTyped(KeyTypedEvent&) { return false; } //!< Return key typed event false when not event handled

		// Mouse bool callbacks
		bool defaultOnMouseDown(MouseButtonPressedEvent&) { return false; } //!< Return mouse pressed event false when not event handled
		bool defaultOnMouseUp(MouseButtonReleasedEvent&) { return false; } //!< Return mouse released event false when not event handled
		bool defaultOnMouseMoved(MouseMovedEvent&) { return false; } //!< Return mouse moved event false when not event handled
		bool defaultOnMouseWheel(MouseScrolledEvent&) { return false; } //!< Return mouse scrolled event false when not event handled
	public:
		// Window set event callbacks
		void setOnCloseCallback(const std::function<bool(WindowCloseEvent&)>& fn) { m_onCloseFunction = fn; }; //!< Window close accessor function
		void setOnResizeCallback(const std::function<bool(WindowResizeEvent&)>& fn) { m_onResizeFunction = fn; }; //!< Window resize accessor function
		void setOnFocusCallback(const std::function<bool(WindowFocusEvent&)>& fn) { m_onFocusFunction = fn; }; //!< Window focus accessor function
		void setOnLostFocusCallback(const std::function<bool(WindowLostFocusEvent&)>& fn) { m_onLostFocusFunction = fn; }; //!< Window lost focus accessor function
		void setOnWindowMovedCallback(const std::function<bool(WindowMovedEvent&)>& fn) { m_onMovedFunction = fn; }; //!< Window moved accessor function

		// Keyboard set event callbacks
		void setOnKeyPressedCallback(const std::function<bool(KeyPressedEvent&)>& fn) { m_onKeyPressedFunction = fn; }; //!< Key pressed accessor function
		void setOnKeyReleasedCallback(const std::function<bool(KeyReleasedEvent&)>& fn) { m_onKeyReleasedFunction = fn; }; //!< Key released accessor function
		void setOnKeyTypedCallback(const std::function<bool(KeyTypedEvent&)>& fn) { m_onKeyTypedFunction = fn; }; //!< Key typed accessor function

		// Mouse set event callbacks
		void setOnMouseDownCallback(const std::function<bool(MouseButtonPressedEvent&)>& fn) { m_onMouseDownFunction = fn; }; //!< Mouse pressed accessor function
		void setOnMouseUpCallback(const std::function<bool(MouseButtonReleasedEvent&)>& fn) { m_onMouseUpFunction = fn; }; //!< Mouse released accessor function
		void setOnMouseMovedCallback(const std::function<bool(MouseMovedEvent&)>& fn) { m_onMouseMovedFunction = fn; }; //!< Mouse moved accessor function
		void setOnMouseWheelCallback(const std::function<bool(MouseScrolledEvent&)>& fn) { m_onMouseWheelFunction = fn; }; //!< Mouse scrolled accessor function

		// Window get event callbacks
		std::function<bool(WindowCloseEvent&)>& getOnCloseCallback() { return m_onCloseFunction; } //!< Getter function to return window close callback
		std::function<bool(WindowResizeEvent&)>& getOnResizeCallback() { return m_onResizeFunction; } //!< Getter function to return window resize callback
		std::function<bool(WindowFocusEvent&)>& getOnFocusCallback() { return m_onFocusFunction; } //!< Getter function to return window focus callback
		std::function<bool(WindowLostFocusEvent&)>& getOnLostFocusCallback() { return m_onLostFocusFunction; } //!< Getter function to return window lost focus callback
		std::function<bool(WindowMovedEvent&)>& getOnWindowMovedCallback() { return m_onMovedFunction; } //!< Getter function to return window moved callback

		// Keyboard get event callbacks
		std::function<bool(KeyPressedEvent&)>& getOnKeyPressedCallback() { return m_onKeyPressedFunction; } //!< Getter function to return keyboard pressed callback
		std::function<bool(KeyReleasedEvent&)>& getOnKeyReleasedCallback() { return m_onKeyReleasedFunction; } //!< Getter function to return keyboard released callback
		std::function<bool(KeyTypedEvent&)>& getOnKeyTypedCallback() { return m_onKeyTypedFunction; } //!< Getter function to return keyboard typed callback

		// Mouse get event callbacks
		std::function<bool(MouseButtonPressedEvent&)>& getOnMouseDownCallback() { return m_onMouseDownFunction; } //!< Getter function to return mouse pressed callback
		std::function<bool(MouseButtonReleasedEvent&)>& getOnMouseUpCallback() { return m_onMouseUpFunction; } //!< Getter function to return mouse released callback
		std::function<bool(MouseMovedEvent&)>& getOnMouseMovedCallback() { return m_onMouseMovedFunction; } //!< Getter function to return mouse moved callback
		std::function<bool(MouseScrolledEvent&)>& getOnMouseWheelCallback() { return m_onMouseWheelFunction; } //!< Getter function to return mouse scrolled callback
	};
}