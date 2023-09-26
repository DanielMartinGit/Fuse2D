#pragma once
#include "Fuse2D/Vendor/GLAD/glad.h"

#include <cstdint>
#include <iostream>

namespace Fuse2DRendering
{
	class Framebuffer
	{
		public:
			virtual void Bind() = 0;
			virtual void Unbind() = 0;
			virtual void DeleteFramebuffer() = 0;

			virtual void Resize(uint32_t width, uint32_t height) = 0;

		public:
			virtual uint32_t GetNative() = 0;
			static Framebuffer* Create(uint32_t width, uint32_t height);
	};
}