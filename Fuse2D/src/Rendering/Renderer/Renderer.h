#pragma once
#include "Fuse2D/src/Rendering/RenderCommand/RenderCommand.h"
#include "Fuse2D/src/Rendering/VertexArray/VertexArray.h"

namespace Fuse2DRendering
{
	class Renderer
	{
		public:
			static void Init(Fuse2DRendering::GraphicsContext* context = nullptr);
			static void Clear();
			static void ClearColour(float r, float g, float b);

			static void DrawIndexedPrimative(Fuse2DRendering::VertexArray* vertexArray, Fuse2DRendering::Shader* shader, unsigned int count = 0);
			static void DrawPrimative(Fuse2DRendering::VertexArray* vertexArray, Fuse2DRendering::Shader* shader, unsigned int count = 0);

			static void Submit(Fuse2DRendering::VertexArray* vertexArray, Fuse2DRendering::Shader* shader);
			static void* GetDevice();

			static Fuse2DRenderAPI::Renderer2DAPI::API GetAPI();
	};
}