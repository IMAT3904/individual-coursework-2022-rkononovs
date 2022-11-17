/** \file eventHandler.h*/
#pragma once

#include "events.h"

#include <functional>

namespace Engine {
	class EventHandler {
	private:
		std::function<bool(WindowCloseEvent&)> m_onCloseFunction = std::bind(&EventHandler::defaultOnClose, this, std::placeholders::_1);
		std::function<bool(WindowResizeEvent&)> m_onResizeFunction = std::bind(&EventHandler::defaultOnResize, this, std::placeholders::_1);
		std::function<bool(WindowFocusEvent&)> m_onFocusFunction = std::bind(&EventHandler::defaultOnFocus, this, std::placeholders::_1);
		std::function<bool(WindowLostFocusEvent&)> m_onLostFocusFunction = std::bind(&EventHandler::defaultOnLostFocus, this, std::placeholders::_1);
		std::function<bool(WindowMovedEvent&)> m_onMovedFunction = std::bind(&EventHandler::defaultOnWindowMoved, this, std::placeholders::_1);

		std::function<bool(KeyPressedEvent&)> m_onKeyPressedFunction = std::bind(&EventHandler::defaultOnKeyPress, this, std::placeholders::_1);
		std::function<bool(KeyReleasedEvent&)> m_onKeyReleasedFunction = std::bind(&EventHandler::defaultOnKeyRelease, this, std::placeholders::_1);
		std::function<bool(KeyTypedEvent&)> m_onKeyTypedFunction = std::bind(&EventHandler::defaultOnKeyTyped, this, std::placeholders::_1);

		std::function<bool(MouseButtonPressedEvent&)> m_onMouseDownFunction = std::bind(&EventHandler::defaultOnMouseDown, this, std::placeholders::_1);
		std::function<bool(MouseButtonReleasedEvent&)> m_onMouseUpFunction = std::bind(&EventHandler::defaultOnMouseUp, this, std::placeholders::_1);
		std::function<bool(MouseMovedEvent&)> m_onMouseMovedFunction = std::bind(&EventHandler::defaultOnMouseMoved, this, std::placeholders::_1);
		std::function<bool(MouseScrolledEvent&)> m_onMouseWheelFunction = std::bind(&EventHandler::defaultOnMouseWheel, this, std::placeholders::_1);

		bool defaultOnClose(WindowCloseEvent&) { return false; }
		bool defaultOnResize(WindowResizeEvent&) { return false; }
		bool defaultOnFocus(WindowFocusEvent&) { return false; }
		bool defaultOnLostFocus(WindowLostFocusEvent&) { return false; }
		bool defaultOnWindowMoved(WindowMovedEvent&) { return false; }

		bool defaultOnKeyPress(KeyPressedEvent&) { return false; }
		bool defaultOnKeyRelease(KeyReleasedEvent&) { return false; }
		bool defaultOnKeyTyped(KeyTypedEvent&) { return false; }

		bool defaultOnMouseDown(MouseButtonPressedEvent&) { return false; }
		bool defaultOnMouseUp(MouseButtonReleasedEvent&) { return false; }
		bool defaultOnMouseMoved(MouseMovedEvent&) { return false; }
		bool defaultOnMouseWheel(MouseScrolledEvent&) { return false; }
	public:
		void setOnCloseCallback(const std::function<bool(WindowCloseEvent&)>& fn) { m_onCloseFunction = fn; };
		void setOnResizeCallback(const std::function<bool(WindowResizeEvent&)>& fn) { m_onResizeFunction = fn; };
		void setOnFocusCallback(const std::function<bool(WindowFocusEvent&)>& fn) { m_onFocusFunction = fn; };
		void setOnLostFocusCallback(const std::function<bool(WindowLostFocusEvent&)>& fn) { m_onLostFocusFunction = fn; };
		void setOnWindowMovedCallback(const std::function<bool(WindowMovedEvent&)>& fn) { m_onMovedFunction = fn; };

		void setOnKeyPressedCallback(const std::function<bool(KeyPressedEvent&)>& fn) { m_onKeyPressedFunction = fn; };
		void setOnKeyReleasedCallback(const std::function<bool(KeyReleasedEvent&)>& fn) { m_onKeyReleasedFunction = fn; };
		void setOnKeyTypedCallback(const std::function<bool(KeyTypedEvent&)>& fn) { m_onKeyTypedFunction = fn; };

		void setOnMouseDownCallback(const std::function<bool(MouseButtonPressedEvent&)>& fn) { m_onMouseDownFunction = fn; };
		void setOnMouseUpCallback(const std::function<bool(MouseButtonReleasedEvent&)>& fn) { m_onMouseUpFunction = fn; };
		void setOnMouseMovedCallback(const std::function<bool(MouseMovedEvent&)>& fn) { m_onMouseMovedFunction = fn; };
		void setOnMouseWheelCallback(const std::function<bool(MouseScrolledEvent&)>& fn) { m_onMouseWheelFunction = fn; };

		std::function<bool(WindowCloseEvent&)>& getOnCloseCallback() { return m_onCloseFunction; }
		std::function<bool(WindowResizeEvent&)>& getOnResizeCallback() { return m_onResizeFunction; }
		std::function<bool(WindowFocusEvent&)>& getOnFocusCallback() { return m_onFocusFunction; }
		std::function<bool(WindowLostFocusEvent&)>& getOnLostFocusCallback() { return m_onLostFocusFunction; }
		std::function<bool(WindowMovedEvent&)>& getOnWindowMovedCallback() { return m_onMovedFunction; }

		std::function<bool(KeyPressedEvent&)>& getOnKeyPressedCallback() { return m_onKeyPressedFunction; }
		std::function<bool(KeyReleasedEvent&)>& getOnKeyReleasedCallback() { return m_onKeyReleasedFunction; }
		std::function<bool(KeyTypedEvent&)>& getOnKeyTypedCallback() { return m_onKeyTypedFunction; }

		std::function<bool(MouseButtonPressedEvent&)>& getOnMouseDownCallback() { return m_onMouseDownFunction; }
		std::function<bool(MouseButtonReleasedEvent&)>& getOnMouseUpCallback() { return m_onMouseUpFunction; }
		std::function<bool(MouseMovedEvent&)>& getOnMouseMovedCallback() { return m_onMouseMovedFunction; }
		std::function<bool(MouseScrolledEvent&)>& getOnMouseWheelCallback() { return m_onMouseWheelFunction; }

		// TODO: Renam all "function's" to callback's
	};
}