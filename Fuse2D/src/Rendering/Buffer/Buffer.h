#pragma once
#include <Fuse2D/Vendor/GLM/glm.hpp>
#include <Fuse2D/Vendor/GLM/gtc/matrix_transform.hpp>
#include <stdint.h>

namespace Fuse2DRendering
{
	struct Vertex
	{
		glm::vec3 m_Position;
		glm::vec3 m_Colour;
		glm::vec2 m_Texture;
	};

	class VertexBuffer
	{
		public:
			virtual ~VertexBuffer() = default;

			virtual void Bind() = 0;
			virtual void Unbind() = 0;
			virtual void SetData(void* data, int size) = 0;

		public:
			virtual void* GetNative() = 0;
			static VertexBuffer* Create(Vertex* vertices, int size);
			static VertexBuffer* Create(int size);
	};

	class IndexBuffer
	{
		public:
			virtual ~IndexBuffer() = default;

			virtual void Bind() = 0;
			virtual void Unbind() = 0;
			virtual uint32_t GetCount() = 0;
			virtual void SetCount(int count) = 0;

		public:
			virtual void* GetNative() = 0;
			static IndexBuffer* Create(uint32_t* indices, int size);
	};
}