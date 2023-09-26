#include "Framebuffer.h"
#include <Fuse2D-Renderer/src/OpenGL/Framebuffer/OpenGLFramebuffer.h>

Fuse2DRendering::Framebuffer* Fuse2DRendering::Framebuffer::Create(uint32_t width, uint32_t height)
{
	return static_cast<Fuse2DRendering::Framebuffer*>(new Fuse2DGraphics::OpenGLFramebuffer(width, height));
}