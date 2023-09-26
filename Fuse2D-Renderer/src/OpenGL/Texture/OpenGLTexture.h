#pragma once
#include "Fuse2D/src/Rendering/Texture/Texture.h"

#include <Fuse2D/Vendor/STB/stb_image.h>
#include <iostream>

namespace Fuse2DGraphics
{
	class OpenGLTexture : public Fuse2DRendering::Texture
	{
		public:
			OpenGLTexture();
			OpenGLTexture(int loadedTexture);
			OpenGLTexture(std::string path, int slot);

			int GetWidth() override;
			int GetHeight() override;
			void* GetNative() override;

			void SetWidth(int width) override;
			void SetHeight(int height) override;
			void SetTexture(uint32_t texture) override;

			void Bind() override;

			uint32_t GetTextureID() override;

		public:
			uint32_t m_TextureID;
			int m_TextureSlot;

		private:
			int m_Width;
			int m_Height;
	};
}