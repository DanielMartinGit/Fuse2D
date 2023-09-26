#include "GraphicsContext.h"

#include "Fuse2D/src/Rendering/Renderer/Renderer.h"
#include "Fuse2D-Renderer/src/OpenGL/GraphicsContext/OpenGLGraphicsContext.h"

Fuse2DRendering::GraphicsContext* Fuse2DRendering::GraphicsContext::Create(void* window)
{
	switch (Fuse2DRendering::Renderer::GetAPI())
	{
		case Fuse2DRenderAPI::Renderer2DAPI::API::OpenGL:
		{
			return static_cast<GraphicsContext*>(new Fuse2DGraphics::OpenGLGraphicsContext(static_cast<GLFWwindow*>(window)));
		}
			break;
	}

	return nullptr;
}