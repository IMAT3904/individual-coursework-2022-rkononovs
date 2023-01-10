/* \file graphicsContext.h */
#pragma once

namespace Engine {
	/** \class GraphicsContext
	*\brief virtual class to provide interface for OpenGL graphics context
	*/
	class GraphicsContext {
	public:
		virtual void init() = 0; //!< Initialize graphics context for the given window
		virtual void swapBuffers() = 0; //!< Swap the front and back buffer
	};
}