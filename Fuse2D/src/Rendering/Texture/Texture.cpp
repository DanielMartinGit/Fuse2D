#include "Texture.h"
#include <Fuse2D/src/Rendering/Renderer/Renderer.h>
#include <Fuse2D-Renderer/src/OpenGL/Texture/OpenGLTexture.h>

Fuse2DRendering::Texture::~Texture() {}

Fuse2DRendering::Texture* Fuse2DRendering::Texture::Create(std::string path, int slot)
{
	switch (Fuse2DRendering::Renderer::GetAPI())
	{
		case Fuse2DRenderAPI::Renderer2DAPI::API::OpenGL:
		{
			return static_cast<Fuse2DRendering::Texture*>(new Fuse2DGraphics::OpenGLTexture(path, slot));
		}
			break;	
	}

	return nullptr;
}
