/* \file graphicsContext.h */
#pragma once

namespace Engine {
	class GraphicsContext {
	private:
	public:
		virtual void init() = 0; //!< Initialize graphics context for the given window
		virtual void swapBuffers() = 0; //!< Swap the front and back buffer
	};
}