#pragma once

#include "Hazel/Renderer/graphicsContext.h"


struct GLFWwindow;

namespace Hazel {
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void init() override;
		virtual void swapBuffers() override;


	private:
		GLFWwindow* m_windowHandle;
	};

}
