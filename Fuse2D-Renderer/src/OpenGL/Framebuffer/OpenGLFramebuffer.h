#pragma once
#include "Fuse2D/src/Rendering/Framebuffer/Framebuffer.h"

#include <iostream>

namespace Fuse2DGraphics
{
	class OpenGLFramebuffer : public Fuse2DRendering::Framebuffer
	{
		public:
			OpenGLFramebuffer(uint32_t width, uint32_t height);
			~OpenGLFramebuffer();

		public:
			void Bind() override;
			void Unbind() override;

			void Resize(uint32_t width, uint32_t height) override;
			void DeleteFramebuffer() override;

		public:
			uint32_t GetNative() override;

		private:
			uint32_t m_CurrentWidth;
			uint32_t m_CurrentHeight;

			uint32_t m_FBO;
			uint32_t m_Framebuffer;
	};
}