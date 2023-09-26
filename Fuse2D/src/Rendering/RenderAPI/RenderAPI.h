#pragma once
#include "Fuse2D/src/Rendering/GraphicsContext/GraphicsContext.h"
#include "Fuse2D/src/Rendering/VertexArray/VertexArray.h"
#include "Fuse2D/src/Rendering/Texture/Texture.h"

namespace Fuse2DRenderAPI
{
	class Renderer2DAPI
	{
		struct Quad
		{
			public:
				float m_Vertices[12] =
				{
					0.5f,  0.5f, 0.0f,  // top right
					0.5f, -0.5f, 0.0f,  // bottom right
				   -0.5f, -0.5f, 0.0f,  // bottom left
				   -0.5f,  0.5f, 0.0f   // top left 
				};

				unsigned int m_Indices[6] =
				{
					// note that we start from 0!
					0, 1, 3,   // first triangle
					1, 2, 3    // second triangle
				};

				unsigned int m_VBO = 0;
				unsigned int m_VAO = 0;
				unsigned int m_EBO = 0;
		};
		
		public:
			enum class API
			{
				None = 0,
				OpenGL = 1
			};

		public:
			virtual ~Renderer2DAPI() = default;

			virtual void Init() = 0;
			virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
			virtual void SetClearColour(float r, float g, float b) = 0;
			virtual void Clear() = 0;

			virtual void EnableWireframeMode(bool state = false) = 0;
			virtual void SetAPI(Renderer2DAPI::API api) { s_API = api; }

		public:
			virtual void* GetDevice() = 0;
			virtual void SetContext(Fuse2DRendering::GraphicsContext* context) = 0;

		public:
			virtual void DrawIndexedPrimitive(Fuse2DRendering::VertexArray* vertexArray, unsigned int count = 0) = 0;
			virtual void DrawPrimitive(Fuse2DRendering::VertexArray* vertexArray, unsigned int count = 0) = 0;

			virtual void BindTexture(Fuse2DRendering::Texture* texture) = 0;

		public:
			static API GetAPI() { return s_API; }
			static Renderer2DAPI* Create();

		private:
			static inline API s_API;
	};
}