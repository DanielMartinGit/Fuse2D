#pragma once
#include "Fuse2D/src/Rendering/RenderAPI/RenderAPI.h"

#include <memory>

namespace Fuse2DRendering
{
	class RenderCommand
	{
		public:
			static void Init(Fuse2DRendering::GraphicsContext* context = nullptr);
			static void ClearColour(float r, float g, float b);
			static void Clear();

			static void EnableWireframeMode(bool state = false);

			static void DrawIndexedPrimative(Fuse2DRendering::VertexArray* vertexArray, unsigned int count = 0);
			static void DrawPrimative(Fuse2DRendering::VertexArray* vertexArray, unsigned int count = 0);

			static void* GetDevice();
			static void BindTexture(Fuse2DRendering::Texture* texture);

		private:
			static std::unique_ptr<Fuse2DRenderAPI::Renderer2DAPI> s_RenderAPI;
	};
}