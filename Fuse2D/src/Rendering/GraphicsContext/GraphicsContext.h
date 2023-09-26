#pragma once

namespace Fuse2DRendering
{
	class GraphicsContext
	{
		public:
			virtual void Init() = 0;
			virtual void* GetNative() = 0;

		public:
			static GraphicsContext* Create(void* window);
	};
}