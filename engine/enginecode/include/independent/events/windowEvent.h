/* \file windowEvent.h */
#pragma once

#include "event.h"
#include <glm/glm.hpp>

namespace Engine {
	class WindowCloseEvent : public Event{
		WindowCloseEvent() {}

		EventType getEventType() const override { return EventType::WindowClose; } //!< Get the event type
		int getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags
	};
}