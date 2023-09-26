#include "VertexArray.h"

#include <Fuse2D/src/Rendering/Renderer/Renderer.h>
#include <Fuse2D-Renderer/src/OpenGL/VertexArray/OpenGLVertexArray.h>

Fuse2DRendering::VertexArray* Fuse2DRendering::VertexArray::Create()
{
	switch (Fuse2DRendering::Renderer::GetAPI())
	{
		case Fuse2DRenderAPI::Renderer2DAPI::API::OpenGL:
		{
			return static_cast<Fuse2DRendering::VertexArray*>(new Fuse2DGraphics::OpenGLVertexArray());
		}
			break;
	}

	return nullptr;
}