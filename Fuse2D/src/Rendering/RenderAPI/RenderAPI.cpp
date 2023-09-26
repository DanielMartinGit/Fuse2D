#include "RenderAPI.h"
#include <Fuse2D-Renderer/src/OpenGL/RenderAPI/OpenGLRenderAPI.h>

Fuse2DRenderAPI::Renderer2DAPI* Fuse2DRenderAPI::Renderer2DAPI::Create()
{
	Fuse2DRenderAPI::Renderer2DAPI::s_API = Fuse2DRenderAPI::Renderer2DAPI::API::OpenGL;

	switch (s_API)
	{
		case API::OpenGL:
		{
			return static_cast<Renderer2DAPI*>(new Fuse2DGraphics::OpenGLRenderAPI());
		}
			break;
	}

	return nullptr;
}