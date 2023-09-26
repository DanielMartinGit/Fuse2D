#pragma once
#include "Fuse2D/src/Rendering/GraphicsContext/GraphicsContext.h"

struct GLFWwindow;

namespace Fuse2DGraphics
{
	class OpenGLGraphicsContext : public Fuse2DRendering::GraphicsContext
	{
		public:
			OpenGLGraphicsContext();
			OpenGLGraphicsContext(GLFWwindow* window);

		public:
			void Init() override;
			void* GetNative() override;

		private:
			GLFWwindow* m_Window;
	};
}