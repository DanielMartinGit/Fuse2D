#pragma once
#include "Fuse2D/src/Rendering/Buffer/Buffer.h"
#include "Fuse2D/src/Rendering/Shader/Shader.h"

namespace Fuse2DRendering
{
	class VertexArray
	{
		public:
			virtual void Bind() = 0;
			virtual void Unbind() = 0;

			virtual void AddVertexBuffer(Fuse2DRendering::VertexBuffer* vertexBuffer) = 0;
			virtual void SetIndexBuffer(Fuse2DRendering::IndexBuffer* indexBuffer) = 0;

			virtual void AddShader(Fuse2DRendering::Shader* vert) = 0;
			virtual void* GetNative() = 0;

			virtual IndexBuffer* GetIndexBuffer() = 0;
			static VertexArray* Create();
	};
}