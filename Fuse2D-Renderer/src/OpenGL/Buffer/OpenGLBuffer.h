#pragma once
#include "Fuse2D/src/Rendering/Buffer/Buffer.h"

namespace Fuse2DGraphics
{
	class OpenGLVertexBuffer : public Fuse2DRendering::VertexBuffer
	{
		public:
			OpenGLVertexBuffer(Fuse2DRendering::Vertex* vertices, int size);
			OpenGLVertexBuffer(int size);

			virtual void Bind() override;
			virtual void Unbind() override;

			void* GetNative() override;
			void SetData(void* data, int size) override;

		private:
			unsigned int m_IVBO;
	};

	class OpenGLIndexBuffer : public Fuse2DRendering::IndexBuffer
	{
		public:
			OpenGLIndexBuffer(unsigned int* indices, int count);

			void Bind() override;
			void Unbind() override;

			void* GetNative() override;

			unsigned int GetCount() override;
			void SetCount(int count) override;

		private:
			int m_ICount;
			unsigned int m_IEBO;
	};
}