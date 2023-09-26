#pragma once

#include <cstdint>
#include <string>

namespace Fuse2DRendering
{
	class Texture
	{
		public:
			virtual ~Texture() = 0;

			virtual int GetWidth() = 0;
			virtual int GetHeight() = 0;
			virtual uint32_t GetTextureID() = 0;

			virtual void SetWidth(int width) = 0;
			virtual void SetHeight(int width) = 0;
			virtual void SetTexture(uint32_t texture) = 0;

			virtual void Bind() = 0;

			virtual void* GetNative() = 0;

			static Texture* Create(std::string path, int slot);
	};

}