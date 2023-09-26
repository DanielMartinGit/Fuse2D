#pragma once

#include "Fuse2D/src/Rendering/VertexArray/VertexArray.h"
#include "Fuse2D/src/Rendering/Shader/Shader.h"

namespace Fuse2DGraphics
{
	class OpenGLVertexArray : public Fuse2DRendering::VertexArray
	{
		public:
			OpenGLVertexArray();

			void Bind() override;
			void Unbind() override;
			void AddVertexBuffer(Fuse2DRendering::VertexBuffer* _pBuffer) override;
			void SetIndexBuffer(Fuse2DRendering::IndexBuffer* _pBuffer) override;
			void AddShader(Fuse2DRendering::Shader* vert) override;
			void* GetNative() override;

			Fuse2DRendering::IndexBuffer* GetIndexBuffer() override;

		private:
			unsigned int m_VAO;
			Fuse2DRendering::IndexBuffer* m_IndexBuffer;
			Fuse2DRendering::VertexBuffer* m_VertexBuffer;

			Fuse2DRendering::Shader* m_Fragment;
			Fuse2DRendering::Shader* m_Vertex;
	};
}
