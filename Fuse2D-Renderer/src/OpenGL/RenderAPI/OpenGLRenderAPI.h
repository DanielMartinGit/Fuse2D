#pragma once
#include "Fuse2D/src/Rendering/RenderAPI/RenderAPI.h"

namespace Fuse2DGraphics
{
	class OpenGLRenderAPI : public Fuse2DRenderAPI::Renderer2DAPI
	{
		public:
			OpenGLRenderAPI();

			void Init() override;
			void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
			void SetClearColour(float x, float y, float z) override;
			void Clear() override;

			void SetContext(Fuse2DRendering::GraphicsContext* _context) override;

			void DrawIndexedPrimitive(Fuse2DRendering::VertexArray* _pVertexArray, unsigned int count = 0) override;
			void DrawPrimitive(Fuse2DRendering::VertexArray* _pVertexArray, unsigned int count = 0) override;

			void EnableWireframeMode(bool state = false) override;

			void* GetDevice() override;

			void BindTexture(Fuse2DRendering::Texture* texture) override;

		private:
			Fuse2DRendering::GraphicsContext* m_Context;

		private:
			bool m_WireframeMode;
	};

}